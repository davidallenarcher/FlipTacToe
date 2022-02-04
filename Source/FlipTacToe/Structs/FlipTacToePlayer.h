// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FlipTacToePieceParameters.h"
#include "FlipTacToePlayer.generated.h"

USTRUCT(BlueprintType)
struct FLIPTACTOE_API FFlipTacToePlayer
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FFlipTacToePieceParameters PieceParameters;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText Status = FText::FromString("Not Ready!");
};
