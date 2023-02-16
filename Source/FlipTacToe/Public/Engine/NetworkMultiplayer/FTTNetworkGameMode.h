// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FTTNetworkGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTNetworkGameMode, Log, All);

UCLASS()
class FLIPTACTOE_API AFTTNetworkGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AFTTNetworkGameMode();

	UFUNCTION()
	virtual void StartGame() const;

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
