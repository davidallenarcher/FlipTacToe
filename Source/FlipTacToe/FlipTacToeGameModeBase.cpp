// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeGameModeBase.h"
#include "FlipTacToePlayerController.h"
#include "FlipTacToePlayerPawn.h"
#include "Kismet/GameplayStatics.h"

void AFlipTacToeGameModeBase::Initialize()
{
	SetPlayerControllerRef();
	SetPlayerRef();
}

void AFlipTacToeGameModeBase::BeginPlay() {
	Initialize();
}

void AFlipTacToeGameModeBase::SetPlayerControllerRef()
{
	if (PlayerControllerRef == nullptr) {
		PlayerControllerRef = (AFlipTacToePlayerController*)UGameplayStatics::GetPlayerController(this, 0);
	}
	PlayerControllerRef->Initialize();
}

void AFlipTacToeGameModeBase::SetPlayerRef()
{
	if (PlayerPawnRef == nullptr) {
		PlayerPawnRef = (AFlipTacToePlayerPawn*)UGameplayStatics::GetPlayerPawn(this, 0);
	}
	PlayerPawnRef->Initialize();
}

void AFlipTacToeGameModeBase::ShowMainMenu()
{
}

void AFlipTacToeGameModeBase::ShowPauseMenu()
{
}

void AFlipTacToeGameModeBase::ShowHotseatMultiplayerOptions()
{
}
