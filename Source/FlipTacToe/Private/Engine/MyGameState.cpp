// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/MyGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogMyGameState);

AMyGameState::AMyGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
}

AMyGameState::~AMyGameState()
{
}

void AMyGameState::StartGame_Implementation(int32 StartingPlayerIndex)
{
	OnStartGame.Broadcast(StartingPlayerIndex);
}

void AMyGameState::BeginPlayerTurn_Multi_Implementation(int32 InActivePlayerIndex)
{
	SetActivePlayerIndex(InActivePlayerIndex);
}

void AMyGameState::EndPlayerTurn_Server_Implementation()
{
	BeginPlayerTurn_Multi((ActivePlayerIndex+1)%2);
}

AGameBoard* AMyGameState::GetGameBoard() const
{
	return GameBoard;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameBoard::StaticClass(), FoundActors);
	GameBoard = static_cast<AGameBoard*>(FoundActors[0]);
	GameBoard->SetOwner(this);
}

int32 AMyGameState::GetActivePlayerIndex()
{
	return ActivePlayerIndex;
}

void AMyGameState::SetActivePlayerIndex(int32 NewActivePlayerIndex)
{
	ActivePlayerIndex = NewActivePlayerIndex;
	OnActivePlayerSet.Broadcast(NewActivePlayerIndex);
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMyGameState, GameBoard);
}
