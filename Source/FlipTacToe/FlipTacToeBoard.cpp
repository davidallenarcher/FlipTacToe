// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeBoard.h"

// Sets default values
AFlipTacToeBoard::AFlipTacToeBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlipTacToeBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlipTacToeBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFlipTacToePiece* AFlipTacToeBoard::getCurrentPieceAt(FFlipTacToeCoordinate Coordinate)
{
	return getSpaceAt(Coordinate)->getCurrentPiece();
}

void AFlipTacToeBoard::Initialize()
{
}

AFlipTacToeBoardSpace* AFlipTacToeBoard::getSpaceAt(FFlipTacToeCoordinate Coordinate)
{
	return SpacesRef[Coordinate.row * 4 + Coordinate.column];
}

