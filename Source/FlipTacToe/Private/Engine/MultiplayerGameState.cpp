// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/MultiplayerGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogMultiplayerGameState);

AMultiplayerGameState_DELETEME::AMultiplayerGameState_DELETEME(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
}

AMultiplayerGameState_DELETEME::~AMultiplayerGameState_DELETEME()
{
}

void AMultiplayerGameState_DELETEME::StartGame_Implementation(int32 StartingPlayerIndex)
{
	OnStartGame.Broadcast(StartingPlayerIndex);
}

void AMultiplayerGameState_DELETEME::BeginPlayerTurn_Multi_Implementation(int32 InActivePlayerIndex)
{
	SetActivePlayerIndex(InActivePlayerIndex);
}

void AMultiplayerGameState_DELETEME::EndPlayerTurn_Server_Implementation()
{
	BeginPlayerTurn_Multi((ActivePlayerIndex+1)%2);
}

AGameBoard* AMultiplayerGameState_DELETEME::GetGameBoard() const
{
	return GameBoard;
}

void AMultiplayerGameState_DELETEME::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameBoard::StaticClass(), FoundActors);
	GameBoard = static_cast<AGameBoard*>(FoundActors[0]);
	GameBoard->SetOwner(this);
}

int32 AMultiplayerGameState_DELETEME::GetActivePlayerIndex()
{
	return ActivePlayerIndex;
}

void AMultiplayerGameState_DELETEME::SetActivePlayerIndex(int32 NewActivePlayerIndex)
{
	ActivePlayerIndex = NewActivePlayerIndex;
	OnActivePlayerSet.Broadcast(NewActivePlayerIndex);
}

void AMultiplayerGameState_DELETEME::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMultiplayerGameState_DELETEME, GameBoard);
}
