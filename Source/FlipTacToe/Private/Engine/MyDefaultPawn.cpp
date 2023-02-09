// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/MyDefaultPawn.h"
#include "Engine/MyPlayerState.h"

DEFINE_LOG_CATEGORY(LogMyDefaultPawn);

AMyDefaultPawn::AMyDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = false;	
}

void AMyDefaultPawn::BeginPlay() 
{
}
