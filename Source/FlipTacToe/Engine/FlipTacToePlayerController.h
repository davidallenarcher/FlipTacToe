// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlipTacToePlayerState.h"
#include "FlipTacToePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API AFlipTacToePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
private:
};
