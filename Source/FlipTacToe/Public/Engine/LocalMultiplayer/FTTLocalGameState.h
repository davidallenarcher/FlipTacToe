// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/GameBoard.h"
#include "GameFramework/GameState.h"
#include "Interfaces/FTTGameStateInterface.h"
#include "Structs/GameCoordinate.h"
#include "FTTLocalGameState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTLocalGameState, Log, All);

UCLASS()
class FLIPTACTOE_API AFTTLocalGameState : public AGameState, public IFTTGameStateInterface
{
	GENERATED_BODY()

public:
	explicit AFTTLocalGameState(const FObjectInitializer& ObjectInitializer);
	virtual ~AFTTLocalGameState() override;

	virtual void BeginPlay() override;

	//** Start FTTGameStateInterface methods *//
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
	//** End FTTGameStateInterface methods *//

	UPROPERTY(BlueprintReadWrite)
	FGameCoordinate HighlightedCoordinate;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 ActivePlayerIndex;
protected:
	UPROPERTY(Replicated)
	AGameBoard* GameBoard;
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
