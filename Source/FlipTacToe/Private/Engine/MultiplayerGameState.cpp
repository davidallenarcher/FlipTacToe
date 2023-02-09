// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/MultiplayerGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogMultiplayerGameState);

AMultiplayerGameState::AMultiplayerGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
}

AMultiplayerGameState::~AMultiplayerGameState()
{
}

void AMultiplayerGameState::StartGame_Implementation(int32 StartingPlayerIndex)
{
	OnStartGame.Broadcast(StartingPlayerIndex);
}

void AMultiplayerGameState::BeginPlayerTurn_Multi_Implementation(int32 InActivePlayerIndex)
{
	SetActivePlayerIndex(InActivePlayerIndex);
}

void AMultiplayerGameState::EndPlayerTurn_Server_Implementation()
{
	BeginPlayerTurn_Multi((ActivePlayerIndex+1)%2);
}

AGameBoard* AMultiplayerGameState::GetGameBoard() const
{
	return GameBoard;
}

void AMultiplayerGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameBoard::StaticClass(), FoundActors);
	GameBoard = static_cast<AGameBoard*>(FoundActors[0]);
	GameBoard->SetOwner(this);
}

int32 AMultiplayerGameState::GetActivePlayerIndex()
{
	return ActivePlayerIndex;
}

void AMultiplayerGameState::SetActivePlayerIndex(int32 NewActivePlayerIndex)
{
	ActivePlayerIndex = NewActivePlayerIndex;
	OnActivePlayerSet.Broadcast(NewActivePlayerIndex);
}

void AMultiplayerGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMultiplayerGameState, GameBoard);
}
