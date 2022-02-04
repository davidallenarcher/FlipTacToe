// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipTacToePiece.h"
#include "../Structs/FlipTacToeCoordinate.h"
#include "FlipTacToeBoardSpace.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToeBoardSpace : public AActor
{
	GENERATED_BODY()
	
public:
	AFlipTacToeBoardSpace();

public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* GetCurrentPiece();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* RemovePiece();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool IsEmpty();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool SetCurrentPiece(AFlipTacToePiece* NewPiece);
	
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Gameplay", meta = (ExposeOnSpawn = "true"))
	FFlipTacToeCoordinate Coordinate;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	USceneComponent* PieceCenterOfRotation;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePiece* CurrentPiece;
};