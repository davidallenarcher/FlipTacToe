// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/MyPlayerController.h"
#include "Engine/Multiplayer/FTTMultiplayerGameState.h"

DEFINE_LOG_CATEGORY(LogMyPlayerController);

AMyPlayerController::AMyPlayerController()
{
	UE_LOG(LogMyPlayerController, Log, TEXT("Constructor[%p]: LocalRole:%s NetMode:%d"), this, *UEnum::GetValueAsString(GetLocalRole()), GetNetMode())
}

AMyPlayerController::~AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	UE_LOG(LogMyPlayerController, Log, TEXT("PRE--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	Super::BeginPlay();
	UE_LOG(LogMyPlayerController, Log, TEXT("POST--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	GameState = static_cast<AFTTMultiplayerGameState*>(GetWorld()->GetGameState());
	if (GameState)
	{
		UE_LOG(LogMyPlayerController, Log, TEXT("BeginPlay[%p]: Starting"), this)
		GameState->OnStartGame.AddDynamic(this, &AMyPlayerController::HandleStartGame);
		GameState->OnActivePlayerSet.AddDynamic(this, &AMyPlayerController::HandleActivePlayerSet);
	} else
	{
		UE_LOG(LogMyPlayerController, Log, TEXT("BeginPlay[%p]: GameState not set"), this)
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMyPlayerController::ReceiveOnPlayerPhaseChanged_Implementation(PlayerPhase NewPlayerPhase)
{
}

void AMyPlayerController::HandleStartGame(int32 StartingPlayerIndex)
{
	if (PlayerIndex == StartingPlayerIndex)
	{
		SetPlayerPhase_Client(PlayerPhase::PlaceOwnPiece);
		UE_LOG(LogMyPlayerController, Log, TEXT("HandleStartGame[%d](%p): PlaceOwnPiece"), PlayerIndex, this);
	} else
	{
		SetPlayerPhase_Client(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogMyPlayerController, Log, TEXT("HandleStartGame[%d](%p): WaitingForOpponent"), PlayerIndex, this);
	}
}

void AMyPlayerController::HandleActivePlayerSet(int32 ActivePlayer)
{
	if (PlayerIndex == ActivePlayer)
	{
		SetPlayerPhase_Client(PlayerPhase::SelectOpponentPiece);
		UE_LOG(LogMyPlayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - SelectOpponentPiece"), PlayerIndex, ActivePlayer);
	} else
	{
		SetPlayerPhase_Client(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogMyPlayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - WaitingForOpponent"), PlayerIndex, ActivePlayer);
	}
}

void AMyPlayerController::HandleSpaceSelect_Implementation(FGameCoordinate SelectedSpace)
{
	if (GameState->ActivePlayerIndex == PlayerIndex)
	{
		const PlayerPhase CurrentPhase = GetPlayerPhase();
		UE_LOG(LogMyPlayerController, Log, TEXT("HandleSpaceSelect[%d](%s): (%d,%d)"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase), SelectedSpace.column, SelectedSpace.row)
		switch (CurrentPhase)
		{
		case PlayerPhase::SelectOpponentPiece:
			SelectSpace(SelectedSpace);
			break;
		case PlayerPhase::FlipOpponentPiece:
			PerformFlipPiece_Server(OpponentSpace, SelectedSpace);
			break;
		case PlayerPhase::PlaceOwnPiece:
			// TODO get shown face from player
			PerformPlacePiece_Server(SelectedSpace, PieceFace::Tails);
			break;
		case PlayerPhase::SelectFace:
			// Performed in blueprints
			break;
		default:
			UE_LOG(LogMyPlayerController, Log, TEXT("HandleSpaceSelect[%d](%s): NOT YOUR TURN"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase));
			break;
		}
	} else
	{
		UE_LOG(LogMyPlayerController, Log, TEXT("HandleSpaceSelect[%d]: NOT YOUR TURN"), PlayerIndex);
	}
}

void AMyPlayerController::SetPlayerPhase_Client_Implementation(PlayerPhase NewPlayerPhase)
{
	if (CurrentPlayerPhase != NewPlayerPhase)
	{
		UE_LOG(LogMyPlayerController, Log, TEXT("SetPlayerPhase_Client[%d] Old:%s New:%s"), PlayerIndex, *UEnum::GetValueAsString(CurrentPlayerPhase), *UEnum::GetValueAsString(NewPlayerPhase))
		CurrentPlayerPhase = NewPlayerPhase;
		ReceiveOnPlayerPhaseChanged(CurrentPlayerPhase);
	}
}

PlayerPhase AMyPlayerController::GetPlayerPhase()
{
	return CurrentPlayerPhase;
}

void AMyPlayerController::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void AMyPlayerController::PerformFlipPiece_Multi_Implementation(FGameCoordinate SourceCoordinate,
                                                                FGameCoordinate DestinationCoordinate)
{
	GameState->GetGameBoard()->FlipPiece(SourceCoordinate, DestinationCoordinate);
}

void AMyPlayerController::PerformPlacePiece_Multi_Implementation(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	GameState->GetGameBoard()->PlacePiece(DestinationCoordinate, PlayerIndex, ShownFace);
	UE_LOG(LogMyPlayerController, Log, TEXT("PerformPlacePiece_Multi[%d]"), PlayerIndex)
}

void AMyPlayerController::SelectSpace(FGameCoordinate SelectedSpace)
{
	bool SpaceIsValid;
	bool SpaceIsEmpty;
	int32 SpacePlayerIndex;
	bool SpaceHeadsShown;

	AGameBoard* GameBoard = GameState->GetGameBoard();
	GameBoard->GetPieceInfoAtSpace(SelectedSpace, SpaceIsValid, SpaceIsEmpty, SpacePlayerIndex, SpaceHeadsShown);
	
	if (SpaceIsValid && !SpaceIsEmpty && SpacePlayerIndex != PlayerIndex)
	{
		OpponentSpace = SelectedSpace;
		SetPlayerPhase_Client(PlayerPhase::FlipOpponentPiece);
	}
}

void AMyPlayerController::PerformPlacePiece_Server_Implementation(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	bool DestinationIsValid;
	bool DestinationIsEmpty;
	int32 DestinationPlayerIndex;
	bool DestinationHeadsShown;

	AGameBoard* GameBoard = GameState->GetGameBoard();
	GameBoard->GetPieceInfoAtSpace(DestinationCoordinate, DestinationIsValid, DestinationIsEmpty, DestinationPlayerIndex, DestinationHeadsShown);
	if (DestinationIsValid && DestinationIsEmpty)
	{
		// TODO move place piece into FTTMultiplayerGameState
		PerformPlacePiece_Multi(DestinationCoordinate, ShownFace);
		GameState->EndPlayerTurn_Server();
	}
}

void AMyPlayerController::SetPlayerIndex_Client_Implementation(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void AMyPlayerController::PerformFlipPiece_Server_Implementation(FGameCoordinate SourceCoordinate, FGameCoordinate DestinationCoordinate)
{
	bool DestinationIsValid;
	bool DestinationIsEmpty;
	int32 DestinationPlayerIndex;
	bool DestinationHeadsShown;

	AGameBoard* GameBoard = GameState->GetGameBoard();
	GameBoard->GetPieceInfoAtSpace(DestinationCoordinate, DestinationIsValid, DestinationIsEmpty, DestinationPlayerIndex, DestinationHeadsShown);
	if (DestinationIsEmpty)
	{
		PerformFlipPiece_Multi(SourceCoordinate, DestinationCoordinate);
		SetPlayerPhase_Client(PlayerPhase::PlaceOwnPiece);
	} else
	{
		// Selected Space has an opponent piece
		if (DestinationPlayerIndex != PlayerIndex)
		{
			OpponentSpace = DestinationCoordinate;
		}
		// Selected Space has active player piece
		else
		{
			SetPlayerPhase_Client(PlayerPhase::SelectOpponentPiece);
		}
	}
}
