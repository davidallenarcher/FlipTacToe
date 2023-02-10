// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GameBoard.h"
#include "GameFramework/GameState.h"
#include "Structs/GameCoordinate.h"
#include "Structs/GameTriple.h"
#include "FTTMultiplayerGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTMultiplayerGameState, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartGame, int32, StartingPlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivePlayerSet, int32, NewActivePlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEndGame, int32, WinnerPlayerIndex, FGameTriple, Winning);

UCLASS()
class FLIPTACTOE_API AFTTMultiplayerGameState : public AGameState
{
	GENERATED_BODY()

public:
	explicit AFTTMultiplayerGameState(const FObjectInitializer& ObjectInitializer);
	virtual ~AFTTMultiplayerGameState() override;

	virtual void BeginPlay() override;

	//** Start Delegates *//
	UPROPERTY(BlueprintAssignable)
	FOnStartGame OnStartGame;

	UPROPERTY(BlueprintAssignable)
	FOnActivePlayerSet OnActivePlayerSet;

	UPROPERTY(BlueprintAssignable)
	FOnEndGame OnEndGame;
	//** End Delegates *//

	//** Start Network Functions *//
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void StartGame_Multi(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void BeginPlayerTurn_Multi(int32 NewActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void EndPlayerTurn_Server();
	//** End Network Functions *//
	
	UFUNCTION(BlueprintPure)
	AGameBoard* GetGameBoard() const;

	UFUNCTION(BlueprintCallable)
	int32 GetActivePlayerIndex();
	
	UFUNCTION(BlueprintCallable)
	void SetActivePlayerIndex(int32 NewActivePlayerIndex);

	UPROPERTY(BlueprintReadWrite)
	FGameCoordinate HighlightedCoordinate;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 ActivePlayerIndex;
private:
	UPROPERTY(Replicated)
	AGameBoard* GameBoard;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
