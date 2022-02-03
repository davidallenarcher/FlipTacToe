// Fill out your copyright notice in the Description page of Project Settings.

#include "FlipTacToeGameMode.h"

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

bool AFlipTacToeGameMode::SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, UMaterialInstance* Material, FlipTacToeFace faceUp)
{
	bool result = false;
	AFlipTacToePiece* NewPiece = GetWorld()->SpawnActor<AFlipTacToePiece>(PieceClass);
	result = GetGameState<AFlipTacToeGameState>()->SetCurrentPieceAt(Coordinate, NewPiece);
	if (!result)
	{
		NewPiece->SetHidden(true);
		NewPiece->ConditionalBeginDestroy();
		NewPiece = nullptr;
	}
	return result;
}

/*
bool AFlipTacToeGameMode::SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece)
{
	return GetGameState<AFlipTacToeGameState>()->SetCurrentPieceAt(Coordinate, NewPiece);
}
//*/
