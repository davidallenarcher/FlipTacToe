// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCoordinate.h"
#include "GameTriple.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FLIPTACTOE_API FGameTriple
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGameCoordinate coordinate0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGameCoordinate coordinate1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FGameCoordinate coordinate2;
};
