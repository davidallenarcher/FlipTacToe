// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeGameState.h"
#include "FlipTacToeBoard.h"
#include "Kismet/GameplayStatics.h"

void AFlipTacToeGameState::BeginPlay()
{

}

AFlipTacToePiece* AFlipTacToeGameState::getCurrentPieceAt(FFlipTacToeCoordinate Coordinate)
{
	return BoardRef->getCurrentPieceAt(Coordinate);
}

