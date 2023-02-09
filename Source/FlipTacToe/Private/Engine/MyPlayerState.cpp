// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/MyPlayerState.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogMyPlayerState);

AMyPlayerState::AMyPlayerState(const class FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	bReplicates = true;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyPlayerState, PlayerSettings);
}
