// David Allen Archer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Structs/FlipTacToePlayerInfo.h"
#include "FlipTacToeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API UFlipTacToeSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	//UPROPERTY( replicated )
	UPROPERTY( replicated )
	FFlipTacToePlayerInfo PlayerInfo;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty, TSizedDefaultAllocator<32> >& OutLifetimeProps) const;
};
