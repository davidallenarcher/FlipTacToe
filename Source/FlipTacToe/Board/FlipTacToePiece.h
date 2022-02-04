// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipTacToePlayer.h"
#include "../Enums/FlipTacToeFace.h"
#include "FlipTacToePiece.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToePiece : public AActor
{
	GENERATED_BODY()
public:	
	AFlipTacToePiece();
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gameplay", BlueprintSetter=SetOwner, meta = (ExposeOnSpawn = "true"))
	UFlipTacToePlayer* Owner;
public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool SetOwner(UFlipTacToePlayer* Player);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FlipTacToeFace GetShownFace();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetShownFace(FlipTacToeFace NewFace);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FlipTacToeFace FlipFace();
private:
	UPROPERTY()
	FlipTacToeFace ShownFace;
};
