// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GameBoard.h"
#include "GameFramework/GameState.h"
#include "Interfaces/FTTGameStateInterface.h"
#include "Structs/GameCoordinate.h"
#include "Structs/GameTriple.h"
#include "FTTNetworkGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTNetworkGameState, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartGame, int32, StartingPlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivePlayerSet, int32, NewActivePlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEndGame, int32, WinnerPlayerIndex, FGameTriple, Winning);

UCLASS()
class FLIPTACTOE_API AFTTNetworkGameState : public AGameState, public IFTTGameStateInterface
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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartGame(int32 StartingPlayerIndex);
	virtual void StartGame_Implementation(int32 StartingPlayerIndex) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeginPlayerTurn(int32 NewActivePlayerIndex);
	virtual void BeginPlayerTurn_Implementation(int32 NewActivePlayerIndex) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndPlayerTurn();
	virtual void EndPlayerTurn_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AGameBoard* GetGameBoard();
	virtual AGameBoard* GetGameBoard_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetActivePlayerIndex();
	virtual int32 GetActivePlayerIndex_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetActivePlayerIndex(int32 NewActivePlayerIndex);
	virtual void SetActivePlayerIndex_Implementation(int32 NewActivePlayerIndex) override;
	
	//** Start Network Functions *//
private:
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void StartGame_Multi(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void BeginPlayerTurn_Multi(int32 NewActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void EndPlayerTurn_Server();
	//** End Network Functions *//
public:
	UPROPERTY(BlueprintReadWrite)
	FGameCoordinate HighlightedCoordinate;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 ActivePlayerIndex;
private:
	UPROPERTY(Replicated)
	AGameBoard* GameBoard;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
