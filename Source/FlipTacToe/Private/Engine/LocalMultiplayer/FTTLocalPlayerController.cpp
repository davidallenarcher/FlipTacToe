// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/LocalMultiplayer/FTTLocalPlayerController.h"
#include "Engine/NetworkMultiplayer/FTTNetworkGameState.h"

DEFINE_LOG_CATEGORY(LogFTTLocalPlayerController);

AFTTLocalPlayerController::AFTTLocalPlayerController()
{
	UE_LOG(LogFTTLocalPlayerController, Log, TEXT("Constructor[%p]: LocalRole:%s NetMode:%d"), this, *UEnum::GetValueAsString(GetLocalRole()), GetNetMode())
}

AFTTLocalPlayerController::~AFTTLocalPlayerController()
{
}

void AFTTLocalPlayerController::BeginPlay()
{
	UE_LOG(LogFTTLocalPlayerController, Log, TEXT("PRE--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	Super::BeginPlay();
	UE_LOG(LogFTTLocalPlayerController, Log, TEXT("POST--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	GameState = static_cast<AFTTNetworkGameState*>(GetWorld()->GetGameState());
	if (GameState)
	{
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("BeginPlay[%p]: Starting"), this)
		GameState->OnStartGame.AddDynamic(this, &AFTTLocalPlayerController::HandleStartGame);
		GameState->OnActivePlayerSet.AddDynamic(this, &AFTTLocalPlayerController::HandleActivePlayerSet);
	} else
	{
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("BeginPlay[%p]: GameState not set"), this)
	}
}

void AFTTLocalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AFTTLocalPlayerController::ReceiveOnPlayerPhaseChanged_Implementation(PlayerPhase NewPlayerPhase)
{
}

void AFTTLocalPlayerController::HandleStartGame(int32 StartingPlayerIndex)
{
	if (PlayerIndex == StartingPlayerIndex)
	{
		SetPlayerPhase(PlayerPhase::PlaceOwnPiece);
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("HandleStartGame[%d](%p): PlaceOwnPiece"), PlayerIndex, this);
	} else
	{
		SetPlayerPhase(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("HandleStartGame[%d](%p): WaitingForOpponent"), PlayerIndex, this);
	}
}

void AFTTLocalPlayerController::HandleActivePlayerSet(int32 ActivePlayer)
{
	if (PlayerIndex == ActivePlayer)
	{
		SetPlayerPhase(PlayerPhase::SelectOpponentPiece);
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - SelectOpponentPiece"), PlayerIndex, ActivePlayer);
	} else
	{
		SetPlayerPhase(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - WaitingForOpponent"), PlayerIndex, ActivePlayer);
	}
}

void AFTTLocalPlayerController::HandleSpaceSelect(FGameCoordinate SelectedSpace)
{
	if (GameState->ActivePlayerIndex == PlayerIndex)
	{
		const PlayerPhase CurrentPhase = GetPlayerPhase();
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("HandleSpaceSelect[%d](%s): (%d,%d)"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase), SelectedSpace.column, SelectedSpace.row)
		switch (CurrentPhase)
		{
		case PlayerPhase::SelectOpponentPiece:
			SelectSpace(SelectedSpace);
			break;
		case PlayerPhase::FlipOpponentPiece:
			PerformFlipPiece(OpponentSpace, SelectedSpace);
			break;
		case PlayerPhase::PlaceOwnPiece:
			// TODO get shown face from player
			PerformPlacePiece(SelectedSpace, PieceFace::Tails);
			break;
		case PlayerPhase::SelectFace:
			// Performed in blueprints
			break;
		default:
			UE_LOG(LogFTTLocalPlayerController, Log, TEXT("HandleSpaceSelect[%d](%s): NOT YOUR TURN"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase));
			break;
		}
	} else
	{
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("HandleSpaceSelect[%d]: NOT YOUR TURN"), PlayerIndex);
	}
}

void AFTTLocalPlayerController::SetPlayerPhase(PlayerPhase NewPlayerPhase)
{
	if (CurrentPlayerPhase != NewPlayerPhase)
	{
		UE_LOG(LogFTTLocalPlayerController, Log, TEXT("SetPlayerPhase_Client[%d] Old:%s New:%s"), PlayerIndex, *UEnum::GetValueAsString(CurrentPlayerPhase), *UEnum::GetValueAsString(NewPlayerPhase))
		CurrentPlayerPhase = NewPlayerPhase;
		ReceiveOnPlayerPhaseChanged(CurrentPlayerPhase);
	}
}

PlayerPhase AFTTLocalPlayerController::GetPlayerPhase()
{
	return CurrentPlayerPhase;
}

void AFTTLocalPlayerController::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void AFTTLocalPlayerController::PerformFlipPiece(FGameCoordinate SourceCoordinate,
                                                                FGameCoordinate DestinationCoordinate)
{
	GameState->GetGameBoard()->FlipPiece(SourceCoordinate, DestinationCoordinate);
}

void AFTTLocalPlayerController::PerformPlacePiece(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	GameState->GetGameBoard()->PlacePiece(DestinationCoordinate, PlayerIndex, ShownFace);
	UE_LOG(LogFTTLocalPlayerController, Log, TEXT("PerformPlacePiece_Multi[%d]"), PlayerIndex)
}

void AFTTLocalPlayerController::SelectSpace(FGameCoordinate SelectedSpace)
{
	AGameBoard* GameBoard = GameState->GetGameBoard();
	
	if (GameBoard->IsValidSpace(SelectedSpace))
	{
		AGamePiece* GamePiece;
		GameBoard->GetPieceAtSpace(SelectedSpace, GamePiece);
		if (GamePiece && GamePiece->PlayerIndex != PlayerIndex)
		{
			OpponentSpace = SelectedSpace;
		}
	}
}

int32 AFTTLocalPlayerController::GetPlayerIndex()
{
	return PlayerIndex;
}

void AFTTLocalPlayerController::PerformPlacePiece_Server(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	AGameBoard* GameBoard = GameState->GetGameBoard();
	if (GameBoard->IsValidSpace(DestinationCoordinate))
	{
		AGamePiece* GamePiece;
		GameBoard->GetPieceAtSpace(DestinationCoordinate, GamePiece);
		if (!GamePiece)
		{
			PerformPlacePiece(DestinationCoordinate, ShownFace);
			GameState->EndPlayerTurn_Server();
		}
	}
}

void AFTTLocalPlayerController::PerformFlipPiece_Server(FGameCoordinate SourceCoordinate, FGameCoordinate DestinationCoordinate)
{
	AGameBoard* GameBoard = GameState->GetGameBoard();
	if (GameBoard->IsValidSpace(SourceCoordinate) && GameBoard->IsValidSpace(DestinationCoordinate))
	{
		AGamePiece* SourcePiece;
		AGamePiece* DestinationPiece;
		GameBoard->GetPieceAtSpace(SourceCoordinate, SourcePiece);
		GameBoard->GetPieceAtSpace(DestinationCoordinate, DestinationPiece);
		if (DestinationPiece)
		{
			PerformFlipPiece(SourceCoordinate, DestinationCoordinate);
			SetPlayerPhase(PlayerPhase::PlaceOwnPiece);
		}
		else
		{
			if (DestinationPiece->PlayerIndex != PlayerIndex)
			{
				OpponentSpace = DestinationCoordinate;
			}
			else
			{
				SetPlayerPhase(PlayerPhase::FlipOpponentPiece);
			}
		}
	}
}
