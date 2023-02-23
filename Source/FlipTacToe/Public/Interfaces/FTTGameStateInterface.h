// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/GameCoordinate.h"
#include "Structs/GameTriple.h"
#include "FTTGameStateInterface.generated.h"

class AGameBoard;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartGame, int32, StartingPlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivePlayerSet, int32, NewActivePlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEndGame, int32, WinnerPlayerIndex, FGameTriple, Winning);

UINTERFACE(Blueprintable)
class FLIPTACTOE_API UFTTGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

class FLIPTACTOE_API IFTTGameStateInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartGame(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeginPlayerTurn(int32 NewActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndPlayerTurn();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AGameBoard* GetGameBoard();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetActivePlayerIndex();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetActivePlayerIndex(int32 NewActivePlayerIndex);
};
