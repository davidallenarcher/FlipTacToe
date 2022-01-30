// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToePlayerPawn.h"

// Sets default values
AFlipTacToePlayerPawn::AFlipTacToePlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Player0Ref.Name = "Player 1";
	Player0Ref.PlayerShape = FlipTacToeShape::SUN;
	Player0Ref.Index = 0;

	Player1Ref.Name = "Player 2";
	Player1Ref.PlayerShape = FlipTacToeShape::MOON;
	Player1Ref.Index = 1;
}

// Called when the game starts or when spawned
void AFlipTacToePlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlipTacToePlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlipTacToePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFlipTacToePlayerPawn::Initialize()
{
}

