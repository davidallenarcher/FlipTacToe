// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeBoard.h"

AFlipTacToeBoard::AFlipTacToeBoard()
{
	PrimaryActorTick.bCanEverTick = false;
}

AFlipTacToePiece* AFlipTacToeBoard::getCurrentPieceAt(FFlipTacToeCoordinate Coordinate)
{
	return getSpaceAt(Coordinate)->GetCurrentPiece();
}

AFlipTacToeBoardSpace* AFlipTacToeBoard::getSpaceAt(FFlipTacToeCoordinate Coordinate)
{
	return Spaces[Coordinate.row * 4 + Coordinate.column];
}

