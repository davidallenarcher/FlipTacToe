// Fill out your copyright notice in the Description page of Project Settings.

#include "FlipTacToePlayerController.h"

void AFlipTacToePlayerController::BeginPlay() {
	AFlipTacToePlayerState* playerState = GetPlayerState<AFlipTacToePlayerState>();
	playerState->SetBaseColor(FLinearColor(1.0f, 1.0f, 1.0f));
	playerState->SetHeadsColor(FLinearColor(0.0f, 1.0f, 0.0f));
	playerState->SetTailsColor(FLinearColor(0.0f, 0.0f, 1.0f));
}