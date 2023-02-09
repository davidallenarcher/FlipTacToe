// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/PlayerSettings.h"
#include "MyPlayerState.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyPlayerState, Log, All);

UCLASS()
class FLIPTACTOE_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	explicit AMyPlayerState(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	FPlayerSettings PlayerSettings;
};
