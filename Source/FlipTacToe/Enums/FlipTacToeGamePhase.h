#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FlipTacToeGamePhase : uint8
{
	GAME_NOT_STARTED UMETA(DisplayName = "Game not started"),
	PLACE_OWN_PIECE UMETA(DisplayName = "Place own piece"),
	FLIP_OPPONENT_PIECE UMETA(DisplayName = "Flip opponent piece"),
	GAME_OVER UMETA(DisplayName = "Game Over")
};
