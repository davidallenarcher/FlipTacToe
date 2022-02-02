// Fill out your copyright notice in the Description page of Project Settings.

#include "FlipTacToeGameMode.h"
#include "FlipTacToePlayerController.h"
#include "FlipTacToePlayerPawn.h"
#include "Kismet/GameplayStatics.h"

AFlipTacToePiece* AFlipTacToeGameMode::GetCurrentPieceAt(FFlipTacToeCoordinate Coordinate)
{
	return GetGameState<AFlipTacToeGameState>()->getCurrentPieceAt(Coordinate);
}

AFlipTacToePiece* AFlipTacToeGameMode::RemovePieceAt(FFlipTacToeCoordinate Coordinate)
{
	return GetGameState<AFlipTacToeGameState>()->RemovePieceAt(Coordinate);
}

bool AFlipTacToeGameMode::IsEmptyAt(FFlipTacToeCoordinate Coordinate)
{
	return GetGameState<AFlipTacToeGameState>()->IsEmptyAt(Coordinate);
}

bool AFlipTacToeGameMode::SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece)
{
	return GetGameState<AFlipTacToeGameState>()->SetCurrentPieceAt(Coordinate, NewPiece);
}
