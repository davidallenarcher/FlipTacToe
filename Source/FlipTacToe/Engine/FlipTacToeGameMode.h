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
	AFlipTacToeGameMode();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AFlipTacToePiece> PieceClass;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* GetCurrentPieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	AFlipTacToePiece* RemovePieceAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool IsEmptyAt(FFlipTacToeCoordinate Coordinate);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool SetCurrentPieceAt(FFlipTacToeCoordinate Coordinate, UMaterialInstance* Material, FlipTacToeFace faceUp);

	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowMainMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowPauseMenu();
	UFUNCTION(BlueprintImplementableEvent, Category = "Navigation")
	void ShowHotseatMultiplayerOptions();
};
