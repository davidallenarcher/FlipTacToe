// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Enums/FlipTacToeFace.h"
#include "FlipTacToePiece.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToePiece : public AActor
{
	GENERATED_BODY()
public:	
	AFlipTacToePiece();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FlipTacToeFace GetShownFace();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetShownFace(FlipTacToeFace NewFace);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FlipTacToeFace FlipFace();
private:
	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gameplay", meta = (ExposeOnSpawn = "true"))
	UPROPERTY()
	FlipTacToeFace ShownFace;
};
