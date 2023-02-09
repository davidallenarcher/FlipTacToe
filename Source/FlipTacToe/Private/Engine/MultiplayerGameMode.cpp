// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/MultiplayerGameMode.h"

#include "Engine/MultiplayerGameState.h"
#include "Engine/MyPlayerState.h"
#include "Engine/MyPlayerController.h"
#include "Engine/MyDefaultPawn.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogMultiplayerGameMode);

AMultiplayerGameMode::AMultiplayerGameMode()
{
	GameStateClass = AMultiplayerGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}

void AMultiplayerGameMode::StartGame()
{
	for (int32 i = 0; i <=1; i++)
	{
		static_cast<AMyPlayerController*>(UGameplayStatics::GetPlayerController(GetWorld(),i))->SetPlayerIndex_Client(i);
	}
	static_cast<AMultiplayerGameState*>(UGameplayStatics::GetGameState(GetWorld()))->StartGame(0);
}

void AMultiplayerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GetNumPlayers() == 2)
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMultiplayerGameMode::StartGame, 1.0f, false);
	}
}

