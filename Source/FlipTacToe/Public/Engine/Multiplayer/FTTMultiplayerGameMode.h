// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FTTMultiplayerGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTMultiplayerGameMode, Log, All);

UCLASS()
class FLIPTACTOE_API AFTTMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AFTTMultiplayerGameMode();

	UFUNCTION()
	virtual void StartGame() const;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
