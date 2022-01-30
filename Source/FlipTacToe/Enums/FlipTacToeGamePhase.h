#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FlipTacToeGamePhase : uint8
{
	PLACE_OWN_PIECE UMETA(DisplayName = "Place own pice"),
	FLIP_OPPONENT_PIECE UMETA(DisplayName = "Flip opponent piece")
};
