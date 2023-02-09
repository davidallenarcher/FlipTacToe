// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SingleplayerGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSinglePlayerGameMode, Log, All);

UCLASS()
class FLIPTACTOE_API ASingleplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASingleplayerGameMode();
};
