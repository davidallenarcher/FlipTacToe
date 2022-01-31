// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipTacToeGameMode.h"
#include "FlipTacToePlayerController.h"
#include "FlipTacToePiece.h"
#include "Structs/FlipTacToeCoordinate.h"
#include "FlipTacToeBoardSpace.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToeBoardSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlipTacToeBoardSpace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	AFlipTacToePiece* getCurrentPiece();

public:
	UPROPERTY( EditInstanceOnly, BlueprintReadWrite, Category="Setup" )
	FFlipTacToeCoordinate Coordinate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePlayerController* PlayerControllerRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToeGameMode* GameModeRef;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePiece* CurrentPieceRef;
};