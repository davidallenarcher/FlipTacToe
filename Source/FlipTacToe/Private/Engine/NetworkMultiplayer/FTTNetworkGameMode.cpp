// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/NetworkMultiplayer/FTTNetworkGameMode.h"
#include "Engine/MyPlayerState.h"
#include "Engine/MyDefaultPawn.h"
#include "Engine/NetworkMultiplayer/FTTNetworkGameState.h"
#include "Engine/NetworkMultiplayer/FTTNetworkPlayerController.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogFTTNetworkGameMode);

AFTTNetworkGameMode::AFTTNetworkGameMode()
{
	GameStateClass = AFTTNetworkGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	PlayerControllerClass = AFTTNetworkPlayerController::StaticClass();
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}

void AFTTNetworkGameMode::StartGame() const
{
	for (int32 i = 0; i <=1; i++)
	{
		APlayerController* PlayerController =
			UGameplayStatics::GetPlayerController(GetWorld(),i);
		AFTTNetworkPlayerController* FTTNetworkPlayerController =
			static_cast<AFTTNetworkPlayerController*>(PlayerController);
		FTTNetworkPlayerController->SetPlayerIndex_Multi(i);
	}
	AGameStateBase* GameStateBase =
		UGameplayStatics::GetGameState(GetWorld());
	AFTTNetworkGameState* FTTNetworkGameState =
		static_cast<AFTTNetworkGameState*>(GameStateBase);
	FTTNetworkGameState->StartGame_Multi(0);
}

void AFTTNetworkGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GetNumPlayers() == 2)
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager()
		.SetTimer(UnusedHandle,
			this,
			&AFTTNetworkGameMode::StartGame,
			1.0f,
			false);
	}
}
