// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/GameCoordinate.h"
#include "Structs/PieceInfo.h"
#include "GameBoard.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGameBoard, Log, All);

class AFTTMultiplayerGameState;

UCLASS()
class FLIPTACTOE_API AGameBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameBoard(const FObjectInitializer& ObjectInitializer);
	virtual ~AGameBoard() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override; 

	UFUNCTION(BlueprintPure)
	static bool IsValidSpace(FGameCoordinate GameCoordinate);
	UFUNCTION(BlueprintPure)
	bool IsEmptySpace(FGameCoordinate GameCoordinate);
	UFUNCTION(BlueprintPure)
	void GetPieceInfoAtSpace(FGameCoordinate GameCoordinate, bool& IsValid, bool& IsEmpty, int32& PlayerIndex, bool& HeadsShown);
	
	UFUNCTION(BlueprintPure)
	void CanPerformMove(FGameCoordinate SourceSpace, FGameCoordinate DestinationSpace, bool& CanPerform);

	UFUNCTION(BlueprintPure)
	void GetSpacesWithFlippablePieces(int32 PlayerIndex, TArray<FGameCoordinate>& FlippableSpaces);
	UFUNCTION(BlueprintPure)
	void GetAvailableFlipSpaces(FGameCoordinate SourceSpace, TArray<FGameCoordinate>& AvailableSpaces);
	UFUNCTION(BlueprintPure)
	void GetEmptySpaces(TArray<FGameCoordinate>& EmptySpaces);
	
	UFUNCTION(BlueprintCallable)
	void FlipPiece(FGameCoordinate SourceSpace, FGameCoordinate DestinationSpace);
	UFUNCTION(BlueprintCallable)
	void PlacePiece(FGameCoordinate DestinationSpace, int32 PlayerIndex, PieceFace ShownFace);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(Replicated, VisibleAnywhere)
	TArray<FPieceInfo> BoardState;
private:
	UFUNCTION()
	static int32 GetIndexForSpace(FGameCoordinate GameCoordinate);
	
	UPROPERTY()
	AFTTMultiplayerGameState* GameState;
};
