// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyDefaultPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyDefaultPawn, Log, All);

UCLASS()
class FLIPTACTOE_API AMyDefaultPawn : public APawn
{
	GENERATED_BODY()
public:
	AMyDefaultPawn();

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;
};
