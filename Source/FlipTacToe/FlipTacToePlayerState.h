// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/FlipTacToePieceParameters.h"
#include "FlipTacToePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API AFlipTacToePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GamePlay")
	FFlipTacToePieceParameters PrimaryParameters;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "GamePlay")
	FFlipTacToePieceParameters SecondaryParameters;
};
