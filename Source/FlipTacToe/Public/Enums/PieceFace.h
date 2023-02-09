// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class PieceFace : uint8
{
	Heads UMETA(DisplayName = "Heads"),
	Tails UMETA(DisplayName = "Tails")
};
