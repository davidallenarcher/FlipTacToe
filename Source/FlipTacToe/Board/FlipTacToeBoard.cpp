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

AFlipTacToePiece* AFlipTacToeBoard::RemovePieceAt(FFlipTacToeCoordinate Coordinate)
{
	return getSpaceAt(Coordinate)->RemovePiece();
}

bool AFlipTacToeBoard::IsEmptyAt(FFlipTacToeCoordinate Coordinate)
{
	return getSpaceAt(Coordinate)->IsEmpty();
}

bool AFlipTacToeBoard::SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece)
{
	return getSpaceAt(Coordinate)->SetCurrentPiece(NewPiece);
}

AFlipTacToeBoardSpace* AFlipTacToeBoard::getSpaceAt(FFlipTacToeCoordinate Coordinate)
{
	return Spaces[Coordinate.row * 4 + Coordinate.column];
}

