// David Allen Archer

#include "FlipTacToeSaveGame.h"
#include "Net/UnrealNetwork.h"

void UFlipTacToeSaveGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty, TSizedDefaultAllocator<32>> & OutLifetimeProps) const
{
	DOREPLIFETIME(UFlipTacToeSaveGame, PlayerInfo);
}
