// Fill out your copyright notice in the Description page of Project Settings.

#include "FlipTacToeGameMode.h"
#include "FlipTacToePlayerPawn.h"
#include "FlipTacToePlayerController.h"
#include "FlipTacToePlayerState.h"

AFlipTacToeGameMode::AFlipTacToeGameMode()
{
	DefaultPawnClass = AFlipTacToePlayerPawn::StaticClass();
	GameStateClass = AFlipTacToeGameState::StaticClass();
	PlayerControllerClass = AFlipTacToePlayerController::StaticClass();
	PlayerStateClass = AFlipTacToePlayerState::StaticClass();
}

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
	float randomZAngle = FMath::RandRange(0, 3) * 90.0f;
	AFlipTacToePiece* NewPiece = GetWorld()->SpawnActor<AFlipTacToePiece>(PieceClass,FVector(),FRotator(0,randomZAngle,0));
	result = GetGameState<AFlipTacToeGameState>()->SetCurrentPieceAt(Coordinate, NewPiece);
	if (!result)
	{
		NewPiece->SetHidden(true);
		NewPiece->ConditionalBeginDestroy();
		NewPiece = nullptr;
	}
	return result;
}
