// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GameBoard.h"
#include "GameFramework/GameState.h"
#include "Structs/GameCoordinate.h"
#include "MultiplayerGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerGameState, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartGame_DELETEME2, int32, StartingPlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivePlayerSet_DELETEME2, int32, NewActivePlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnEndGame_DELETEME2, int32, WinnerPlayerIndex, FGameCoordinate, Coord1, FGameCoordinate, Coord2, FGameCoordinate, Coord3);

UCLASS()
class FLIPTACTOE_API AMultiplayerGameState_DELETEME : public AGameState
{
	GENERATED_BODY()

public:
	explicit AMultiplayerGameState_DELETEME(const FObjectInitializer& ObjectInitializer);
	virtual ~AMultiplayerGameState_DELETEME() override;

	UPROPERTY(BlueprintAssignable)
	FOnStartGame_DELETEME2 OnStartGame;

	UPROPERTY(BlueprintAssignable)
	FOnActivePlayerSet_DELETEME2 OnActivePlayerSet;

	UPROPERTY(BlueprintAssignable)
	FOnEndGame_DELETEME2 OnEndGame;
	
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetGameBoard, Replicated)
	AGameBoard* GameBoard;

	UPROPERTY(BlueprintReadWrite)
	FGameCoordinate HighlightedCoordinate;
	
	UFUNCTION(BlueprintPure)
	AGameBoard* GetGameBoard() const;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	int32 GetActivePlayerIndex();
	
	UFUNCTION(BlueprintCallable)
	void SetActivePlayerIndex(int32 NewActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void StartGame(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void BeginPlayerTurn_Multi(int32 InActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void EndPlayerTurn_Server();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 ActivePlayerIndex;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
