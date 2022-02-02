#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FlipTacToeGamePhase : uint8
{
	GAME_NOT_STARTED UMETA(DisplayName = "Game not started"),
	FLIP_OPPONENT_PIECE UMETA(DisplayName = "Flip opponent piece"),
	PLACE_OWN_PIECE UMETA(DisplayName = "Place own piece"),
	GAME_OVER UMETA(DisplayName = "Game Over")
};
