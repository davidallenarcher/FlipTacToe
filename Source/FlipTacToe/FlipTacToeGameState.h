// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FlipTacToeBoard.h"
#include "FlipTacToeGameState.generated.h"

// Forward Declarations
class AFlipTacToeBoard;
class AFlipTacToePiece;

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
	AFlipTacToeBoard* BoardRef;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePiece* SelectedPieceRef;
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	AFlipTacToePiece* getCurrentPieceAt(FFlipTacToeCoordinate Coordinate);

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	TArray<FFlipTacToePlayer> Players;
};
