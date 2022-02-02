// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FlipTacToeCoordinate.h"
#include "FlipTacToeTriple.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FLIPTACTOE_API FFlipTacToeTriple
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FFlipTacToeCoordinate coordinate0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FFlipTacToeCoordinate coordinate1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FFlipTacToeCoordinate coordinate2;
};
