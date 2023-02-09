// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerGameState.h"
#include "Enums/PlayerPhase.h"
#include "GameFramework/PlayerController.h"
#include "Structs/GameCoordinate.h"
#include "MyPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyPlayerController, Log, All);

UCLASS()
class FLIPTACTOE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	virtual ~AMyPlayerController() override;
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, DisplayName="OnPlayerPhaseChanged")
	void ReceiveOnPlayerPhaseChanged(PlayerPhase NewPlayerPhase);
	
	UFUNCTION(BlueprintCallable)
	void HandleStartGame(int32 StartingPlayerIndex);

	UFUNCTION(BlueprintCallable)
	void HandleActivePlayerSet(int32 ActivePlayerIndex);
	
	UFUNCTION(BlueprintCallable)
	void HandleSpaceSelect(FGameCoordinate SelectedSpace);

	UFUNCTION(BlueprintGetter)
	PlayerPhase GetPlayerPhase();

	UPROPERTY(BlueprintGetter=GetPlayerPhase, DisplayName="PlayerPhase")
	PlayerPhase CurrentPlayerPhase;

	/* BEGIN Networked Events */
	UFUNCTION(BlueprintCallable, Client, Reliable)
	void SetPlayerIndex_Client(int32 NewPlayerIndex);

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void SetPlayerPhase_Client(PlayerPhase NewPlayerPhase);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void PerformFlipPiece_Server(FGameCoordinate SourceCoordinate, FGameCoordinate DestinationCoordinate);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void PerformPlacePiece_Server(FGameCoordinate DestinationCoordinate, PieceFace ShownFace);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void PerformFlipPiece_Multi(FGameCoordinate SourceCoordinate, FGameCoordinate DestinationCoordinate);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void PerformPlacePiece_Multi(FGameCoordinate DestinationCoordinate, PieceFace ShownFace);
	/* END Networked Events */
	
	UFUNCTION(BlueprintCallable)
	void SelectSpace(FGameCoordinate SelectedSpace);
	
private:
	UPROPERTY()
	AMultiplayerGameState* GameState;
	
	UPROPERTY()
	int32 PlayerIndex;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameCoordinate OpponentSpace;
};
