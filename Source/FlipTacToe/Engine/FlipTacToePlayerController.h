// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlipTacToePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API AFlipTacToePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
};
