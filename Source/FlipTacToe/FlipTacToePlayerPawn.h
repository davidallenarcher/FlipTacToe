// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Structs/FlipTacToePlayer.h"
#include "FlipTacToePlayerPawn.generated.h"

UCLASS()
class FLIPTACTOE_API AFlipTacToePlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlipTacToePlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
/*
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	FFlipTacToePlayer Player0Ref;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	FFlipTacToePlayer Player1Ref;
//*/
};
