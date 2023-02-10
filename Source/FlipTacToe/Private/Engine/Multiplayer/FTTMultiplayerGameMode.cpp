// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Multiplayer/FTTMultiplayerGameMode.h"

#include "Engine/MyPlayerState.h"
#include "Engine/Multiplayer/FTTMultiplayerController.h"
#include "Engine/MyDefaultPawn.h"
#include "Engine/Multiplayer/FTTMultiplayerGameState.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogFTTMultiplayerGameMode);

AFTTMultiplayerGameMode::AFTTMultiplayerGameMode()
{
	GameStateClass = AFTTMultiplayerGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	PlayerControllerClass = AFTTMultiplayerController::StaticClass();
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}

void AFTTMultiplayerGameMode::StartGame() const
{
	for (int32 i = 0; i <=1; i++)
	{
		APlayerController* PlayerController =
			UGameplayStatics::GetPlayerController(GetWorld(),i);
		AFTTMultiplayerController* MyPlayerController =
			static_cast<AFTTMultiplayerController*>(PlayerController);
		MyPlayerController->SetPlayerIndex_Client(i);
		MyPlayerController->SetPlayerIndex(i);
	}
	AGameStateBase* GameStateBase =
		UGameplayStatics::GetGameState(GetWorld());
	AFTTMultiplayerGameState* FTTMultiplayerGameState =
		static_cast<AFTTMultiplayerGameState*>(GameStateBase);
	FTTMultiplayerGameState->StartGame_Multi(0);
}

void AFTTMultiplayerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GetNumPlayers() == 2)
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager()
		.SetTimer(UnusedHandle,
			this,
			&AFTTMultiplayerGameMode::StartGame,
			1.0f,
			false);
	}
}
