// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/LocalMultiplayer/FTTLocalGameMode.h"

#include "Engine/LocalMultiplayer/FTTLocalGameState.h"
#include "Engine/LocalMultiplayer/FTTLocalPlayerController.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogFTTLocalGameMode);

AFTTLocalGameMode::AFTTLocalGameMode()
{
	GameStateClass = AFTTLocalGameState::StaticClass();
	PlayerControllerClass = AFTTLocalPlayerController::StaticClass();
}
