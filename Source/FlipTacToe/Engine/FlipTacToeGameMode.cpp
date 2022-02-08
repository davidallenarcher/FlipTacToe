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
	return GetGameState<AFlipTacToeGameState>()->GetCurrentPieceAt(Coordinate);
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
	AFlipTacToePiece* NewPiece;
	bool result = false;
	float randomZAngle = FMath::RandRange(0, 3) * 90.0f;
	
	if (GetGameState<AFlipTacToeGameState>()->IsEmptyAt(Coordinate)) {
		AFlipTacToePlayerState* playerState = (AFlipTacToePlayerState*)GetGameState<AFlipTacToeGameState>()->PlayerArray[0];
		NewPiece = playerState->GetPiece();
		NewPiece->SetActorRelativeRotation(FRotator(0.0f, randomZAngle, 0.0f).Quaternion());
		GetGameState<AFlipTacToeGameState>()->SetCurrentPieceAt(Coordinate, NewPiece);
		result = true;
	}

	return result;
}
