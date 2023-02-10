// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/Multiplayer/FTTMultiplayerGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogFTTMultiplayerGameState);

AFTTMultiplayerGameState::AFTTMultiplayerGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
}

AFTTMultiplayerGameState::~AFTTMultiplayerGameState()
{
}

void AFTTMultiplayerGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameBoard::StaticClass(), FoundActors);
	GameBoard = static_cast<AGameBoard*>(FoundActors[0]);
	GameBoard->SetOwner(this);
}

void AFTTMultiplayerGameState::StartGame_Multi_Implementation(int32 StartingPlayerIndex)
{
	OnStartGame.Broadcast(StartingPlayerIndex);
}

void AFTTMultiplayerGameState::BeginPlayerTurn_Multi_Implementation(int32 NewActivePlayerIndex)
{
	SetActivePlayerIndex(NewActivePlayerIndex);
}

void AFTTMultiplayerGameState::EndPlayerTurn_Server_Implementation()
{
	BeginPlayerTurn_Multi((ActivePlayerIndex+1)%2);
}

AGameBoard* AFTTMultiplayerGameState::GetGameBoard() const
{
	return GameBoard;
}

int32 AFTTMultiplayerGameState::GetActivePlayerIndex()
{
	return ActivePlayerIndex;
}

void AFTTMultiplayerGameState::SetActivePlayerIndex(int32 NewActivePlayerIndex)
{
	ActivePlayerIndex = NewActivePlayerIndex;
	OnActivePlayerSet.Broadcast(NewActivePlayerIndex);
}

void AFTTMultiplayerGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFTTMultiplayerGameState, GameBoard);
}
