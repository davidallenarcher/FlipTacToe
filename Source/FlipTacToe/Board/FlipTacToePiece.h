// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Enums/FlipTacToeFace.h"
#include "../Enums/FlipTacToeDirection.h"
#include "FlipTacToePiece.generated.h"

class UFlipTacToePlayer;

UCLASS()
class FLIPTACTOE_API AFlipTacToePiece : public AActor
{
	GENERATED_BODY()
public:	
	AFlipTacToePiece();
public:
	UFUNCTION(BlueprintSetter)
	void SetOwningPlayer(UFlipTacToePlayer* Player);

	UFUNCTION(BlueprintGetter)
	UFlipTacToePlayer* GetOwningPlayer();
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FlipTacToeFace GetShownFace();
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetShownFace(FlipTacToeFace NewFace);
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FlipTacToeFace FlipFace(FlipTacToeDirection direction);

private:
	UPROPERTY(EditInstanceOnly, BlueprintSetter = SetOwningPlayer, BlueprintGetter = GetOwningPlayer, meta = (ExposeOnSpawn = "true"))
	UFlipTacToePlayer* OwningPlayer;
	UPROPERTY()
	FlipTacToeFace ShownFace;
};
