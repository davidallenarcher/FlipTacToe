// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/PlayerPhase.h"
#include "Enums/PieceFace.h"
#include "GameFramework/PlayerController.h"
#include "Structs/GameCoordinate.h"
#include "FTTLocalPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFTTLocalPlayerController, Log, All);

class AFTTNetworkGameState;

UCLASS()
class FLIPTACTOE_API AFTTLocalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFTTLocalPlayerController();
	virtual ~AFTTLocalPlayerController() override;
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerPhaseChanged(PlayerPhase NewPlayerPhase);
	
	UFUNCTION(BlueprintCallable)
	void HandleStartGame(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable)
	void HandleActivePlayerSet(int32 ActivePlayerIndex);
	
	UFUNCTION(BlueprintGetter)
	PlayerPhase GetPlayerPhase() const;

	UFUNCTION()
	void SetPlayerIndex(int32 NewPlayerIndex);
	
	UFUNCTION(BlueprintCallable)
	void HandleSpaceSelect(FGameCoordinate SelectedSpace);

	UFUNCTION(BlueprintCallable)
	void SetPlayerPhase(PlayerPhase NewPlayerPhase);

	UFUNCTION(BlueprintCallable)
	void PerformFlipPiece(FGameCoordinate SourceCoordinate, FGameCoordinate DestinationCoordinate);

	UFUNCTION(BlueprintCallable)
	void PerformPlacePiece(FGameCoordinate DestinationCoordinate, PieceFace ShownFace);
	
	UFUNCTION(BlueprintCallable)
	void SelectSpace(FGameCoordinate SelectedSpace);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetPlayerIndex();

	UPROPERTY(BlueprintGetter=GetPlayerPhase, DisplayName="PlayerPhase")
	PlayerPhase CurrentPlayerPhase;
	
private:
	UPROPERTY()
	AFTTNetworkGameState* GameState;
	
	UPROPERTY()
	int32 PlayerIndex;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameCoordinate OpponentSpace;
};
