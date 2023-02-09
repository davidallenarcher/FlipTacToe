// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerGameMode, Log, All);

UCLASS()
class FLIPTACTOE_API AMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMultiplayerGameMode();

	void StartGame();
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
