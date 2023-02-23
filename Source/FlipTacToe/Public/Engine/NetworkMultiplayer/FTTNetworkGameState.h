// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LocalMultiplayer/FTTLocalGameState.h"
#include "Game/GameBoard.h"
#include "Interfaces/FTTGameStateInterface.h"
#include "Structs/GameCoordinate.h"
#include "FTTNetworkGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTNetworkGameState, Log, All);

UCLASS()
class FLIPTACTOE_API AFTTNetworkGameState : public AFTTLocalGameState
{
	GENERATED_BODY()

public:
	explicit AFTTNetworkGameState(const FObjectInitializer& ObjectInitializer);
	virtual ~AFTTNetworkGameState() override;

	virtual void BeginPlay() override;

	//** Start Delegates *//
	UPROPERTY(BlueprintAssignable)
	FOnStartGame OnStartGame;

	UPROPERTY(BlueprintAssignable)
	FOnActivePlayerSet OnActivePlayerSet;

	UPROPERTY(BlueprintAssignable)
	FOnEndGame OnEndGame;
	//** End Delegates *//

	//** Start FTTGameStateInterface methods *//
	virtual void StartGame_Implementation(int32 StartingPlayerIndex) override;

	virtual void BeginPlayerTurn_Implementation(int32 NewActivePlayerIndex) override;

	virtual void EndPlayerTurn_Implementation() override;

	virtual AGameBoard* GetGameBoard_Implementation() override;

	virtual int32 GetActivePlayerIndex_Implementation() override;

	virtual void SetActivePlayerIndex_Implementation(int32 NewActivePlayerIndex) override;
	//** End FTTGameStateInterface methods *//
	
private:
	//** Start Network Functions *//
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void StartGame_Multi(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void BeginPlayerTurn_Multi(int32 NewActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void EndPlayerTurn_Server();
	//** End Network Functions *//
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
