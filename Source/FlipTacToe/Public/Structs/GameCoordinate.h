// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCoordinate.generated.h"

USTRUCT(BlueprintType)
struct FLIPTACTOE_API FGameCoordinate
{
	GENERATED_BODY()

	explicit FGameCoordinate(int32 const c = 0, int32 const r = 0) : column(c), row(r) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 row;

	bool operator==(const FGameCoordinate& Other) const
	{
		return (row == Other.row && column == Other.column);
	}
};
