// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/NetworkMultiplayer/FTTNetworkGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogFTTNetworkGameState);

AFTTNetworkGameState::AFTTNetworkGameState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bReplicates = true;
}

AFTTNetworkGameState::~AFTTNetworkGameState()
{
}

void AFTTNetworkGameState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameBoard::StaticClass(), FoundActors);
	GameBoard = static_cast<AGameBoard*>(FoundActors[0]);
	GameBoard->SetOwner(this);
}

/** Begin IFTTGameStateInterface Events */
void AFTTNetworkGameState::StartGame_Implementation(int32 StartingPlayerIndex)
{
	StartGame_Multi(StartingPlayerIndex);
}

void AFTTNetworkGameState::BeginPlayerTurn_Implementation(int32 NewActivePlayerIndex)
{
	BeginPlayerTurn_Multi(NewActivePlayerIndex);
}

void AFTTNetworkGameState::EndPlayerTurn_Implementation()
{
	EndPlayerTurn_Server();
}

AGameBoard* AFTTNetworkGameState::GetGameBoard_Implementation()
{
	return GameBoard;
}

int32 AFTTNetworkGameState::GetActivePlayerIndex_Implementation()
{
	return ActivePlayerIndex;
}

void AFTTNetworkGameState::SetActivePlayerIndex_Implementation(int32 NewActivePlayerIndex)
{
	ActivePlayerIndex = NewActivePlayerIndex;
	OnActivePlayerSet.Broadcast(NewActivePlayerIndex);
}
/** End IFTTGameStateInterface Events */

//** Start Network Functions *//
void AFTTNetworkGameState::StartGame_Multi_Implementation(int32 StartingPlayerIndex)
{
	OnStartGame.Broadcast(StartingPlayerIndex);
}

void AFTTNetworkGameState::BeginPlayerTurn_Multi_Implementation(int32 NewActivePlayerIndex)
{
	SetActivePlayerIndex(NewActivePlayerIndex);
}

void AFTTNetworkGameState::EndPlayerTurn_Server_Implementation()
{
	BeginPlayerTurn_Multi((ActivePlayerIndex+1)%2);
}
//** End Network Functions *//

void AFTTNetworkGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFTTNetworkGameState, GameBoard);
}
