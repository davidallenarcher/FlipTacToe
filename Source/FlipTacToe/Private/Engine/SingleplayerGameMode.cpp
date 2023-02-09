// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/SingleplayerGameMode.h"
#include "Engine/MyPlayerState.h"
#include "Engine/MyPlayerController.h"
#include "Engine/MyDefaultPawn.h"
#include "Engine/MyGameState.h"

DEFINE_LOG_CATEGORY(LogSinglePlayerGameMode)

ASingleplayerGameMode::ASingleplayerGameMode()
{
	GameStateClass = AMyGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}
