// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/LocalMultiplayer/FTTLocalGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogFTTLocalGameState);

AFTTLocalGameState::AFTTLocalGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
}

AFTTLocalGameState::~AFTTLocalGameState()
{
}

void AFTTLocalGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameBoard::StaticClass(), FoundActors);
	GameBoard = static_cast<AGameBoard*>(FoundActors[0]);
	GameBoard->SetOwner(this);
}

void AFTTLocalGameState::StartGame_Implementation(int32 StartingPlayerIndex)
{
}

void AFTTLocalGameState::BeginPlayerTurn_Implementation(int32 NewActivePlayerIndex)
{
	SetActivePlayerIndex(NewActivePlayerIndex);
}

void AFTTLocalGameState::EndPlayerTurn_Implementation()
{
	BeginPlayerTurn((ActivePlayerIndex+1)%2);
}

AGameBoard* AFTTLocalGameState::GetGameBoard_Implementation()
{
	return GameBoard;
}

int32 AFTTLocalGameState::GetActivePlayerIndex_Implementation()
{
	return ActivePlayerIndex;
}

void AFTTLocalGameState::SetActivePlayerIndex_Implementation(int32 NewActivePlayerIndex)
{
	ActivePlayerIndex = NewActivePlayerIndex;
}

void AFTTLocalGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFTTLocalGameState, GameBoard);
}
