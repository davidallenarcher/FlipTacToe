// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeGameState.h"
#include "FlipTacToeBoard.h"
#include "Kismet/GameplayStatics.h"

void AFlipTacToeGameState::BeginPlay()
{
	Initialize();
}

void AFlipTacToeGameState::Initialize()
{
	SetBoardRef();
	SetPiecesRef();
}

void AFlipTacToeGameState::SetBoardRef()
{
	if (BoardRef == nullptr) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(this, AFlipTacToeBoard::StaticClass(), FoundActors);
		BoardRef = (AFlipTacToeBoard*)FoundActors[0];
	}
	if (BoardRef != nullptr) {
		BoardRef->Initialize();
	}
}

void AFlipTacToeGameState::SetPiecesRef()
{
	if (PiecesRef.Num() == 0) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(this, AFlipTacToePiece::StaticClass(), FoundActors);
		for (AActor* FoundActor : FoundActors) {
			ProcessPiece((AFlipTacToePiece*)FoundActor);
		}
	}
}

void AFlipTacToeGameState::ProcessPiece(AFlipTacToePiece* Piece)
{
	AFlipTacToePiece* TempPiece = Piece;
	TempPiece->Initialize();
}
