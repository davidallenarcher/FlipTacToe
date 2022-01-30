// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipTacToeBoardSpace.h"
#include "Structs/FlipTacToePlayer.h"
#include "FlipTacToeBoard.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToeBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlipTacToeBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	TArray<AFlipTacToeBoardSpace*> SpacesRef;
};
