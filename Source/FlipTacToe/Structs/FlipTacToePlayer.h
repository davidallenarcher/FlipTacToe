// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Enums/FlipTacToeShape.h"
#include "FlipTacToePlayer.generated.h"

USTRUCT(BlueprintType)
struct FLIPTACTOE_API FFlipTacToePlayer
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FlipTacToeShape PlayerShape;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Index;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool HasLegalMoves;
};
