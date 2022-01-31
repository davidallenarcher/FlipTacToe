// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipTacToeBoardSpace.h"
#include "Structs/FlipTacToePlayer.h"
#include "FlipTacToeBoard.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToeBoard : public AActor
{
	GENERATED_BODY()
	
public:
	AFlipTacToeBoard();

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	AFlipTacToePiece* getCurrentPieceAt(FFlipTacToeCoordinate Coordinate);
private:
	UFUNCTION()
	AFlipTacToeBoardSpace* getSpaceAt(FFlipTacToeCoordinate Coordinate);
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	TArray<AFlipTacToeBoardSpace*> Spaces;
};
