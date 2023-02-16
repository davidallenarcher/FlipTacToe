// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GameBoard.h"
#include "GameFramework/GameState.h"
#include "Structs/GameCoordinate.h"
#include "Structs/GameTriple.h"
#include "FTTLocalGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTLocalGameState, Log, All);

UCLASS()
class FLIPTACTOE_API AFTTLocalGameState : public AGameState
{
	GENERATED_BODY()

public:
	explicit AFTTLocalGameState(const FObjectInitializer& ObjectInitializer);
	virtual ~AFTTLocalGameState() override;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartGame(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable)
	void BeginPlayerTurn(int32 NewActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable)
	void EndPlayerTurn();
	
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
