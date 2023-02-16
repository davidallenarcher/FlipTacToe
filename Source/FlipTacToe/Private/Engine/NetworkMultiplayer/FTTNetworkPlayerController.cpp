// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/NetworkMultiplayer/FTTNetworkPlayerController.h"
#include "Engine/NetworkMultiplayer/FTTNetworkGameState.h"

DEFINE_LOG_CATEGORY(LogFTTNetworkPlayerController);

AFTTNetworkPlayerController::AFTTNetworkPlayerController()
{
	UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("Constructor[%p]: LocalRole:%s NetMode:%d"), this, *UEnum::GetValueAsString(GetLocalRole()), GetNetMode())
}

AFTTNetworkPlayerController::~AFTTNetworkPlayerController()
{
}

void AFTTNetworkPlayerController::BeginPlay()
{
	UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("PRE--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	Super::BeginPlay();
	UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("POST--BeginPlay[%p]: NetMode:%d"), this, GetNetMode())
	GameState = static_cast<AFTTNetworkGameState*>(GetWorld()->GetGameState());
	if (GameState)
	{
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("BeginPlay[%p]: Starting"), this)
		GameState->OnStartGame.AddDynamic(this, &AFTTNetworkPlayerController::HandleStartGame);
		GameState->OnActivePlayerSet.AddDynamic(this, &AFTTNetworkPlayerController::HandleActivePlayerSet);
	} else
	{
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("BeginPlay[%p]: GameState not set"), this)
	}
}

void AFTTNetworkPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AFTTNetworkPlayerController::ReceiveOnPlayerPhaseChanged_Implementation(PlayerPhase NewPlayerPhase)
{
}

void AFTTNetworkPlayerController::HandleStartGame(int32 StartingPlayerIndex)
{
	if (PlayerIndex == StartingPlayerIndex)
	{
		SetPlayerPhase_Multi(PlayerPhase::PlaceOwnPiece);
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("HandleStartGame[%d](%p): PlaceOwnPiece"), PlayerIndex, this);
	} else
	{
		SetPlayerPhase_Multi(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("HandleStartGame[%d](%p): WaitingForOpponent"), PlayerIndex, this);
	}
}

void AFTTNetworkPlayerController::HandleActivePlayerSet(int32 ActivePlayer)
{
	if (PlayerIndex == ActivePlayer)
	{
		SetPlayerPhase_Multi(PlayerPhase::SelectOpponentPiece);
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - SelectOpponentPiece"), PlayerIndex, ActivePlayer);
	} else
	{
		SetPlayerPhase_Multi(PlayerPhase::WaitingForOpponent);
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("HandleActivePlayerSet[%d]: NewActivePlayer:%d - WaitingForOpponent"), PlayerIndex, ActivePlayer);
	}
}

void AFTTNetworkPlayerController::HandleSpaceSelect_Server_Implementation(FGameCoordinate SelectedSpace)
{
	if (GameState->ActivePlayerIndex == PlayerIndex)
	{
		const PlayerPhase CurrentPhase = GetPlayerPhase();
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("HandleSpaceSelect[%d](%s): (%d,%d)"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase), SelectedSpace.column, SelectedSpace.row)
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
			UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("HandleSpaceSelect[%d](%s): NOT YOUR TURN"), PlayerIndex, *UEnum::GetValueAsString(CurrentPhase));
			break;
		}
	} else
	{
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("HandleSpaceSelect[%d]: NOT YOUR TURN"), PlayerIndex);
	}
}

void AFTTNetworkPlayerController::SetPlayerPhase_Multi_Implementation(PlayerPhase NewPlayerPhase)
{
	if (CurrentPlayerPhase != NewPlayerPhase)
	{
		UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("SetPlayerPhase_Client[%d] Old:%s New:%s"), PlayerIndex, *UEnum::GetValueAsString(CurrentPlayerPhase), *UEnum::GetValueAsString(NewPlayerPhase))
		CurrentPlayerPhase = NewPlayerPhase;
		ReceiveOnPlayerPhaseChanged(CurrentPlayerPhase);
	}
}

PlayerPhase AFTTNetworkPlayerController::GetPlayerPhase()
{
	return CurrentPlayerPhase;
}

void AFTTNetworkPlayerController::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void AFTTNetworkPlayerController::PerformFlipPiece_Multi_Implementation(FGameCoordinate SourceCoordinate,
                                                                FGameCoordinate DestinationCoordinate)
{
	GameState->GetGameBoard()->FlipPiece(SourceCoordinate, DestinationCoordinate);
}

void AFTTNetworkPlayerController::PerformPlacePiece_Multi_Implementation(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	GameState->GetGameBoard()->PlacePiece(DestinationCoordinate, PlayerIndex, ShownFace);
	UE_LOG(LogFTTNetworkPlayerController, Log, TEXT("PerformPlacePiece_Multi[%d]"), PlayerIndex)
}

void AFTTNetworkPlayerController::SelectSpace(FGameCoordinate SelectedSpace)
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

int32 AFTTNetworkPlayerController::GetPlayerIndex()
{
	return PlayerIndex;
}

void AFTTNetworkPlayerController::PerformPlacePiece_Server_Implementation(FGameCoordinate DestinationCoordinate, PieceFace ShownFace)
{
	AGameBoard* GameBoard = GameState->GetGameBoard();
	if (GameBoard->IsValidSpace(DestinationCoordinate))
	{
		AGamePiece* GamePiece;
		GameBoard->GetPieceAtSpace(DestinationCoordinate, GamePiece);
		if (!GamePiece)
		{
			PerformPlacePiece_Multi(DestinationCoordinate, ShownFace);
			GameState->EndPlayerTurn_Server();
		}
	}
}

void AFTTNetworkPlayerController::SetPlayerIndex_Multi_Implementation(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void AFTTNetworkPlayerController::PerformFlipPiece_Server_Implementation(FGameCoordinate SourceCoordinate, FGameCoordinate DestinationCoordinate)
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
			PerformFlipPiece_Multi(SourceCoordinate, DestinationCoordinate);
			SetPlayerPhase_Multi(PlayerPhase::PlaceOwnPiece);
		}
		else
		{
			if (DestinationPiece->PlayerIndex != PlayerIndex)
			{
				OpponentSpace = DestinationCoordinate;
			}
			else
			{
				SetPlayerPhase_Multi(PlayerPhase::FlipOpponentPiece);
			}
		}
	}
}
