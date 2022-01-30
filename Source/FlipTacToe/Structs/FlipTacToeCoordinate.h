// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FlipTacToeCoordinate.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FLIPTACTOE_API FFlipTacToeCoordinate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 row;
};
