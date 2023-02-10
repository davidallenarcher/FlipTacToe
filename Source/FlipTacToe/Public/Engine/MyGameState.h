// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GameBoard.h"
#include "GameFramework/GameState.h"
#include "Structs/GameCoordinate.h"
#include "MyGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyGameState, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartGame_DELETEME, int32, StartingPlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivePlayerSet_DELETEME, int32, NewActivePlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnEndGame_DELETEME, int32, WinnerPlayerIndex, FGameCoordinate, Coord1, FGameCoordinate, Coord2, FGameCoordinate, Coord3);

UCLASS()
class FLIPTACTOE_API AMyGameState_Deprecated : public AGameState
{
	GENERATED_BODY()

public:
	explicit AMyGameState_Deprecated(const FObjectInitializer& ObjectInitializer);
	virtual ~AMyGameState_Deprecated() override;

	UPROPERTY(BlueprintAssignable)
	FOnStartGame_DELETEME OnStartGame;

	UPROPERTY(BlueprintAssignable)
	FOnActivePlayerSet_DELETEME OnActivePlayerSet;

	UPROPERTY(BlueprintAssignable)
	FOnEndGame_DELETEME OnEndGame;
	
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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
