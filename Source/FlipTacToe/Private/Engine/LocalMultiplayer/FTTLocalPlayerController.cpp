// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/LocalMultiplayer/FTTLocalPlayerController.h"
#include "Engine/NetworkMultiplayer/FTTNetworkGameState.h"

DEFINE_LOG_CATEGORY(LogFTTLocalPlayerController);

AFTTLocalPlayerController::AFTTLocalPlayerController()
{
}

AFTTLocalPlayerController::~AFTTLocalPlayerController()
{
}

void AFTTLocalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameState = static_cast<AFTTNetworkGameState*>(GetWorld()->GetGameState());
	if (GameState)
	{
		//GameState->OnStartGame.AddDynamic(this, &AFTTLocalPlayerController::HandleStartGame);
		//GameState->OnActivePlayerSet.AddDynamic(this, &AFTTLocalPlayerController::HandleActivePlayerSet);
	}
}

void AFTTLocalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AFTTLocalPlayerController::OnPlayerPhaseChanged_Implementation(PlayerPhase NewPlayerPhase)
{
}

void AFTTLocalPlayerController::HandleStartGame(int32 StartingPlayerIndex)
{
	SetPlayerPhase(PlayerPhase::PlaceOwnPiece);
}

void AFTTLocalPlayerController::HandleActivePlayerSet(int32 ActivePlayer)
{
	int32 OtherPlayer = (ActivePlayer+1)%2;
	TArray<FGameCoordinate> FlippablePieces;
	GameState->GetGameBoard()->GetSpacesWithFlippablePieces(OtherPlayer, FlippablePieces);
	if (FlippablePieces.Num() == 0)
	{
		SetPlayerPhase(PlayerPhase::SelectOpponentPiece);
	} else
	{
		SetPlayerPhase(PlayerPhase::PlaceOwnPiece);
	}
}

void AFTTLocalPlayerController::HandleSpaceSelect(FGameCoordinate SelectedSpace)
{
	const PlayerPhase CurrentPhase = GetPlayerPhase();
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
		break;
	}
}

void AFTTLocalPlayerController::SetPlayerPhase(PlayerPhase NewPlayerPhase)
{
	if (CurrentPlayerPhase != NewPlayerPhase)
	{
		CurrentPlayerPhase = NewPlayerPhase;
		OnPlayerPhaseChanged(CurrentPlayerPhase);
	}
}

PlayerPhase AFTTLocalPlayerController::GetPlayerPhase() const
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
	AGameBoard* GameBoard = GameState->GetGameBoard();
	if (GameBoard->IsValidSpace(SourceCoordinate) && GameBoard->IsValidSpace(DestinationCoordinate))
	{
		AGamePiece* SourcePiece;
		AGamePiece* DestinationPiece;
		GameBoard->GetPieceAtSpace(SourceCoordinate, SourcePiece);
		GameBoard->GetPieceAtSpace(DestinationCoordinate, DestinationPiece);
		if (DestinationPiece)
		{
			GameState->GetGameBoard()->FlipPiece(SourceCoordinate, DestinationCoordinate);
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

void AFTTLocalPlayerController::PerformPlacePiece(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	AGameBoard* GameBoard = GameState->GetGameBoard();
	if (GameBoard->IsValidSpace(DestinationCoordinate))
	{
		AGamePiece* GamePiece;
		GameBoard->GetPieceAtSpace(DestinationCoordinate, GamePiece);
		if (!GamePiece)
		{
			GameState->GetGameBoard()->PlacePiece(DestinationCoordinate, PlayerIndex, ShownFace);
			GameState->EndPlayerTurn_Server();
		}
	}
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
