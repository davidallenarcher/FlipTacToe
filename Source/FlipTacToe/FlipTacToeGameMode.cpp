// Fill out your copyright notice in the Description page of Project Settings.

#include "FlipTacToeGameMode.h"
#include "FlipTacToePlayerController.h"
#include "FlipTacToePlayerPawn.h"
#include "Kismet/GameplayStatics.h"

AFlipTacToePiece* AFlipTacToeGameMode::getCurrentPieceAt(FFlipTacToeCoordinate Coordinate)
{
	return FlipTacToeGameState->getCurrentPieceAt(Coordinate);
}

AFlipTacToePiece* AFlipTacToeGameMode::RemovePieceAt(FFlipTacToeCoordinate Coordinate)
{
	return FlipTacToeGameState->RemovePieceAt(Coordinate);
}

bool AFlipTacToeGameMode::IsEmptyAt(FFlipTacToeCoordinate Coordinate)
{
	return FlipTacToeGameState->IsEmptyAt(Coordinate);
}

bool AFlipTacToeGameMode::SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece)
{
	return FlipTacToeGameState->SetCurrentPieceAt(Coordinate, NewPiece);
}
