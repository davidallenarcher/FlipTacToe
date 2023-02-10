// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/Multiplayer/FTTMultiplayerController.h"
#include "Engine/Multiplayer/FTTMultiplayerGameState.h"

DEFINE_LOG_CATEGORY(LogFTTMultiplayerController);

AFTTMultiplayerController::AFTTMultiplayerController()
{
	UE_LOG(LogFTTMultiplayerController, Log, TEXT("Constructor[%p]: LocalRole:%s NetMode:%d"), this, *UEnum::GetValueAsString(GetLocalRole()), GetNetMode())
}

AFTTMultiplayerController::~AFTTMultiplayerController()
{
}

void AFTTMultiplayerController::BeginPlay()
{
	UE_LOG(LogFTTMultiplayerController, Log, TEXT("PRE--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	Super::BeginPlay();
	UE_LOG(LogFTTMultiplayerController, Log, TEXT("POST--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	GameState = static_cast<AFTTMultiplayerGameState*>(GetWorld()->GetGameState());
	if (GameState)
	{
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("BeginPlay[%p]: Starting"), this)
		GameState->OnStartGame.AddDynamic(this, &AFTTMultiplayerController::HandleStartGame);
		GameState->OnActivePlayerSet.AddDynamic(this, &AFTTMultiplayerController::HandleActivePlayerSet);
	} else
	{
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("BeginPlay[%p]: GameState not set"), this)
	}
}

void AFTTMultiplayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AFTTMultiplayerController::ReceiveOnPlayerPhaseChanged_Implementation(PlayerPhase NewPlayerPhase)
{
}

void AFTTMultiplayerController::HandleStartGame(int32 StartingPlayerIndex)
{
	if (PlayerIndex == StartingPlayerIndex)
	{
		SetPlayerPhase_Client(PlayerPhase::PlaceOwnPiece);
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("HandleStartGame[%d](%p): PlaceOwnPiece"), PlayerIndex, this);
	} else
	{
		SetPlayerPhase_Client(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("HandleStartGame[%d](%p): WaitingForOpponent"), PlayerIndex, this);
	}
}

void AFTTMultiplayerController::HandleActivePlayerSet(int32 ActivePlayer)
{
	if (PlayerIndex == ActivePlayer)
	{
		SetPlayerPhase_Client(PlayerPhase::SelectOpponentPiece);
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - SelectOpponentPiece"), PlayerIndex, ActivePlayer);
	} else
	{
		SetPlayerPhase_Client(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - WaitingForOpponent"), PlayerIndex, ActivePlayer);
	}
}

void AFTTMultiplayerController::HandleSpaceSelect_Implementation(FGameCoordinate SelectedSpace)
{
	if (GameState->ActivePlayerIndex == PlayerIndex)
	{
		const PlayerPhase CurrentPhase = GetPlayerPhase();
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("HandleSpaceSelect[%d](%s): (%d,%d)"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase), SelectedSpace.column, SelectedSpace.row)
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
			UE_LOG(LogFTTMultiplayerController, Log, TEXT("HandleSpaceSelect[%d](%s): NOT YOUR TURN"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase));
			break;
		}
	} else
	{
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("HandleSpaceSelect[%d]: NOT YOUR TURN"), PlayerIndex);
	}
}

void AFTTMultiplayerController::SetPlayerPhase_Client_Implementation(PlayerPhase NewPlayerPhase)
{
	if (CurrentPlayerPhase != NewPlayerPhase)
	{
		UE_LOG(LogFTTMultiplayerController, Log, TEXT("SetPlayerPhase_Client[%d] Old:%s New:%s"), PlayerIndex, *UEnum::GetValueAsString(CurrentPlayerPhase), *UEnum::GetValueAsString(NewPlayerPhase))
		CurrentPlayerPhase = NewPlayerPhase;
		ReceiveOnPlayerPhaseChanged(CurrentPlayerPhase);
	}
}

PlayerPhase AFTTMultiplayerController::GetPlayerPhase()
{
	return CurrentPlayerPhase;
}

void AFTTMultiplayerController::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void AFTTMultiplayerController::PerformFlipPiece_Multi_Implementation(FGameCoordinate SourceCoordinate,
                                                                FGameCoordinate DestinationCoordinate)
{
	GameState->GetGameBoard()->FlipPiece(SourceCoordinate, DestinationCoordinate);
}

void AFTTMultiplayerController::PerformPlacePiece_Multi_Implementation(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	GameState->GetGameBoard()->PlacePiece(DestinationCoordinate, PlayerIndex, ShownFace);
	UE_LOG(LogFTTMultiplayerController, Log, TEXT("PerformPlacePiece_Multi[%d]"), PlayerIndex)
}

void AFTTMultiplayerController::SelectSpace(FGameCoordinate SelectedSpace)
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

void AFTTMultiplayerController::PerformPlacePiece_Server_Implementation(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
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

void AFTTMultiplayerController::SetPlayerIndex_Client_Implementation(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void AFTTMultiplayerController::PerformFlipPiece_Server_Implementation(FGameCoordinate SourceCoordinate, FGameCoordinate DestinationCoordinate)
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
