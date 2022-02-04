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
	LastStartPlayerIndex = 2;

	NewGame();
}

void AFlipTacToeGameState::NewGame()
{
	if (LastStartPlayerIndex == 1) 
	{
		CurrentPlayerIndex = 2;
	}
	else
	{
		CurrentPlayerIndex = 1;
	}
	LastStartPlayerIndex = CurrentPlayerIndex;
	CurrentGamePhase = FlipTacToeGamePhase::GAME_NOT_STARTED;
}

FFlipTacToePlayer AFlipTacToeGameState::GetCurrentPlayer()
{
	return (CurrentPlayerIndex == 1)?Player1:Player2;
}

FlipTacToeGamePhase AFlipTacToeGameState::GetCurrentGamePhase()
{
	return CurrentGamePhase;
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
	bool result = false;
	if (CurrentGamePhase == FlipTacToeGamePhase::PLACE_OWN_PIECE) 
	{
		result = Board->SetCurrentPieceAt(Coordinate, NewPiece);
		if (result)
		{
			if (CurrentPlayerIndex == 1)
			{
				CurrentPlayerIndex = 2;
			}
			else
			{
				CurrentPlayerIndex = 1;
			}
			CurrentGamePhase = FlipTacToeGamePhase::FLIP_OPPONENT_PIECE;
		}
	}
	return result;
}

bool AFlipTacToeGameState::FlipPiece(FFlipTacToeCoordinate FromCoordinate, FFlipTacToeCoordinate ToCoordinate)
{
	bool result = false;
	int deltaColumn = FromCoordinate.column - ToCoordinate.column;
	int deltaRow = FromCoordinate.row - ToCoordinate.row;
	if (deltaColumn * deltaColumn + deltaRow * deltaRow == 1) {
		if (!Board->IsEmptyAt(FromCoordinate) && Board->IsEmptyAt(ToCoordinate)) {
			Board->SetCurrentPieceAt(ToCoordinate, Board->RemovePieceAt(FromCoordinate));
			TArray<FFlipTacToeTriple> WinningLines = GetWinningLines();
			if (WinningLines.Num() > 0) 
			{
				CurrentGamePhase = FlipTacToeGamePhase::GAME_OVER;
			}
			else 
			{
				CurrentGamePhase = FlipTacToeGamePhase::PLACE_OWN_PIECE;
			}
		}
	}
	return result;
}

TArray<FFlipTacToeTriple> AFlipTacToeGameState::GetWinningLines()
{
	// TODO actually search for winning lines
	return TArray<FFlipTacToeTriple>();
}


