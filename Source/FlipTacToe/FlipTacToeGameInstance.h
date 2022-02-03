// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FlipTacToeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API UFlipTacToeGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	FText P_ServerName;
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowMainMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowHostMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowServerMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowOptionsMenu();

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowLoadingScreen();

	UFUNCTION(BlueprintNativeEvent, Category = "Navigation")
	void LaunchLobby(bool IsLanEnabled, const FText &ServerName);
};
