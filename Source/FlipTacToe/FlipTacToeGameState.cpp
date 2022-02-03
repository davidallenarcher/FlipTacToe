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

void AFlipTacToeGameState::NewGame()
{
	CurrentPlayer = Player1;
	CurrentGamePhase = FlipTacToeGamePhase::GAME_NOT_STARTED;
}

FFlipTacToePlayer AFlipTacToeGameState::GetCurrentPlayer()
{
	return CurrentPlayer;
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
	const bool result = Board->SetCurrentPieceAt(Coordinate, NewPiece);
	if (result)
	{
		if (CurrentPlayer.ID == Player1.ID)
		{
			CurrentPlayer = Player2;
		}
		else
		{
			CurrentPlayer = Player1;
		}
		CurrentGamePhase = FlipTacToeGamePhase::FLIP_OPPONENT_PIECE;
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


