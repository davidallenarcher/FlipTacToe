// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FTTLocalGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTLocalGameMode, Log, All);

UCLASS()
class FLIPTACTOE_API AFTTLocalGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AFTTLocalGameMode();
};
