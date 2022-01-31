// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeGameMode.h"
#include "FlipTacToePlayerController.h"
#include "FlipTacToePlayerPawn.h"
#include "Kismet/GameplayStatics.h"

void AFlipTacToeGameMode::Initialize()
{
	SetPlayerControllerRef();
	SetPlayerRef();
}

void AFlipTacToeGameMode::BeginPlay() {
	Initialize();
}

void AFlipTacToeGameMode::SetPlayerControllerRef()
{
	if (PlayerControllerRef == nullptr) {
		PlayerControllerRef = (AFlipTacToePlayerController*)UGameplayStatics::GetPlayerController(this, 0);
	}
	PlayerControllerRef->Initialize();
}

void AFlipTacToeGameMode::SetPlayerRef()
{
	if (PlayerPawnRef == nullptr) {
		PlayerPawnRef = (AFlipTacToePlayerPawn*)UGameplayStatics::GetPlayerPawn(this, 0);
	}
	PlayerPawnRef->Initialize();
}

