// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/SingleplayerGameMode.h"
#include "Engine/MyPlayerState.h"
#include "Engine/MyDefaultPawn.h"
#include "Engine/MyGameState.h"

DEFINE_LOG_CATEGORY(LogSinglePlayerGameMode)

ASingleplayerGameMode::ASingleplayerGameMode()
{
	PlayerStateClass = AMyPlayerState::StaticClass();
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}
