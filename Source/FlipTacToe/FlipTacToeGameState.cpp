// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeGameState.h"
#include "FlipTacToeBoard.h"
#include "Kismet/GameplayStatics.h"

void AFlipTacToeGameState::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = false;

	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFlipTacToeBoard::StaticClass(), Actors);

	if (Actors.Num() > 0) 
	{
		Board = (AFlipTacToeBoard*)Actors[0];
	}
}

AFlipTacToePiece* AFlipTacToeGameState::getCurrentPieceAt(FFlipTacToeCoordinate Coordinate)
{
	return Board->getCurrentPieceAt(Coordinate);
}

AFlipTacToePiece* AFlipTacToeGameState::RemovePieceAt(FFlipTacToeCoordinate Coordinate)
{
	return Board->RemovePieceAt(Coordinate);
}

bool AFlipTacToeGameState::IsEmptyAt(FFlipTacToeCoordinate Coordinate)
{
	return Board->IsEmptyAt(Coordinate);
}

bool AFlipTacToeGameState::SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece)
{
	return Board->SetCurrentPieceAt(Coordinate, NewPiece);
}


