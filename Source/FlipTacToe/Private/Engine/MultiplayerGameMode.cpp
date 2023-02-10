// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/MultiplayerGameMode.h"

#include "Engine/MultiplayerGameState.h"
#include "Engine/MyPlayerState.h"
#include "Engine/MyPlayerController.h"
#include "Engine/MyDefaultPawn.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogMultiplayerGameMode);

AMultiplayerGameMode_DELETEME::AMultiplayerGameMode_DELETEME()
{
	GameStateClass = AMultiplayerGameState_DELETEME::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}

void AMultiplayerGameMode_DELETEME::StartGame()
{
	for (int32 i = 0; i <=1; i++)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),i);
		AMyPlayerController* MyPlayerController = static_cast<AMyPlayerController*>(PlayerController);
		UE_LOG(LogMultiplayerGameMode, Log, TEXT("StartGame(%d)[%p]: GameMode: %p"), i, MyPlayerController, this)
		MyPlayerController->SetPlayerIndex_Client(i);
		MyPlayerController->SetPlayerIndex(i);
	}
	OnGameReady.Broadcast();
	AMultiplayerGameState_DELETEME* MultiplayerGameState = static_cast<AMultiplayerGameState_DELETEME*>(GameState);
	MultiplayerGameState->StartGame(0);
}

void AMultiplayerGameMode_DELETEME::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GetNumPlayers() == 2)
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMultiplayerGameMode_DELETEME::StartGame, 1.0f, false);
	}
}

