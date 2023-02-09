// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerSettings.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FLIPTACTOE_API FPlayerSettings
{
	GENERATED_BODY()

	explicit FPlayerSettings(
			FName n = FName("Player"),
			FLinearColor b = FLinearColor(0,0,0),
			FLinearColor h = FLinearColor(0,0,0),
			FLinearColor t = FLinearColor(0,0,0),
			UTexture* i = nullptr
		):
		Name(n),
		BaseColor(b),
		HeadsColor(h),
		TailsColor(t),
		IconTexture(i)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BaseColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor HeadsColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor TailsColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* IconTexture;
};
