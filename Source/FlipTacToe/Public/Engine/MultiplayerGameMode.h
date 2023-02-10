// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerGameMode, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameReady_DELETEME);

UCLASS()
class FLIPTACTOE_API AMultiplayerGameMode_DELETEME : public AGameMode
{
	GENERATED_BODY()

public:
	AMultiplayerGameMode_DELETEME();

	FOnGameReady_DELETEME OnGameReady;
	
	void StartGame();
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
