// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipTacToeBoardSpace.h"
#include "FlipTacToeBoard.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToeBoard : public AActor
{
	GENERATED_BODY()
	
public:
	AFlipTacToeBoard();

public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* getCurrentPieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* RemovePieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool IsEmptyAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToeBoardSpace* getSpaceAt(FFlipTacToeCoordinate Coordinate);
private:
	
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	TArray<AFlipTacToeBoardSpace*> Spaces;
};
