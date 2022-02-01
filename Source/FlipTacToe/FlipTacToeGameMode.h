// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FlipTacToeGameState.h"
#include "FlipTacToeGameMode.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToeGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToeGameState* FlipTacToeGameState;
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	AFlipTacToePiece* getCurrentPieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* RemovePieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool IsEmptyAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, AFlipTacToePiece* NewPiece);

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowMainMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowPauseMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowHotseatMultiplayerOptions();
};
