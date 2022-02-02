// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FlipTacToeBoard.h"
#include "Enums/FlipTacToeGamePhase.h"
#include "FlipTacToeGameState.generated.h"

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API AFlipTacToeGameState : public AGameState
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToeBoard* Board;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePiece* SelectedPiece;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gameplay")
	FlipTacToeGamePhase CurrentGamePhase;
public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* getCurrentPieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* RemovePieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool IsEmptyAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece);
};
