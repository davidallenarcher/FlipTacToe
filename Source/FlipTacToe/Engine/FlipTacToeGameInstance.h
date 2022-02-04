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
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Networking")
	FText P_ServerName;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Navigation")
	void ShowMainMenu();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Navigation")
	void ShowHostMenu();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Navigation")
	void ShowServerMenu();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Navigation")
	void ShowOptionsMenu();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Navigation")
	void ShowLoadingScreen();

	/*
	// https://www.youtube.com/watch?v=78XJYBfWXAA&list=PLZlv_N0_O1gYqSlbGQVKsRg6fpxWndZqZ&index=3
	//UFUNCTION(BlueprintNativeEvent, Category = "Navigation")
	UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
	void LaunchLobby(bool IsLanEnabled, const FText &ServerName);
	UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
	void JoinServer(...);
	*/
};
