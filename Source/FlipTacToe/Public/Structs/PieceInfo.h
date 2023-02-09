// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enums/PieceFace.h"
#include "PieceInfo.generated.h"

USTRUCT(BlueprintType)
struct FLIPTACTOE_API FPieceInfo
{
	GENERATED_BODY()

	explicit FPieceInfo(int32 const index = -1, PieceFace const face = PieceFace::Heads)
	: PlayerIndex(index), ShownFace(face)
	{
		
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	PieceFace ShownFace;

	bool IsEmpty() const
	{
		return (PlayerIndex != 0 && PlayerIndex != 1);
	}

	bool IsHeadsShown() const
	{
		return ShownFace == PieceFace::Heads;
	}
};
