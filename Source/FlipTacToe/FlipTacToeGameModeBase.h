// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlipTacToeGameModeBase.generated.h"

// Forward Declarations
class AFlipTacToePlayerController;
class AFlipTacToePlayerPawn;

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API AFlipTacToeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePlayerController *PlayerControllerRef;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePlayerPawn *PlayerPawnRef;
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayerControllerRef();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPlayerRef();

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowMainMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowPauseMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowHotseatMultiplayerOptions();
};
