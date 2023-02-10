// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/MyGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogMyGameState);

AMyGameState_Deprecated::AMyGameState_Deprecated(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
}

AMyGameState_Deprecated::~AMyGameState_Deprecated()
{
}

void AMyGameState_Deprecated::StartGame_Implementation(int32 StartingPlayerIndex)
{
	OnStartGame.Broadcast(StartingPlayerIndex);
}

void AMyGameState_Deprecated::BeginPlayerTurn_Multi_Implementation(int32 InActivePlayerIndex)
{
	SetActivePlayerIndex(InActivePlayerIndex);
}

void AMyGameState_Deprecated::EndPlayerTurn_Server_Implementation()
{
	BeginPlayerTurn_Multi((ActivePlayerIndex+1)%2);
}

AGameBoard* AMyGameState_Deprecated::GetGameBoard() const
{
	return GameBoard;
}

void AMyGameState_Deprecated::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameBoard::StaticClass(), FoundActors);
	GameBoard = static_cast<AGameBoard*>(FoundActors[0]);
	GameBoard->SetOwner(this);
}

int32 AMyGameState_Deprecated::GetActivePlayerIndex()
{
	return ActivePlayerIndex;
}

void AMyGameState_Deprecated::SetActivePlayerIndex(int32 NewActivePlayerIndex)
{
	ActivePlayerIndex = NewActivePlayerIndex;
	OnActivePlayerSet.Broadcast(NewActivePlayerIndex);
}

void AMyGameState_Deprecated::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMyGameState_Deprecated, GameBoard);
}
