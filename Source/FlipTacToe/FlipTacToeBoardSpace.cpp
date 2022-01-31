// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeBoardSpace.h"

// Sets default values
AFlipTacToeBoardSpace::AFlipTacToeBoardSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlipTacToeBoardSpace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlipTacToeBoardSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFlipTacToePiece* AFlipTacToeBoardSpace::getCurrentPiece()
{
	return CurrentPieceRef;
}


