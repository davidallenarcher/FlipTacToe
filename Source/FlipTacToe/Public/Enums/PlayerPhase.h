#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class PlayerPhase : uint8
{
	Winner UMETA(DisplayName = "Winner"),
	Loser UMETA(DisplayName = "Loser"),
	WaitingForOpponent UMETA(DisplayName = "Waiting for Opponent"),
	SelectOpponentPiece UMETA(DisplayName = "Select opponent piece"),
	FlipOpponentPiece UMETA(DisplayName = "Flip opponent piece"),
	PlaceOwnPiece UMETA(DisplayName = "Place own piece"),
	SelectFace UMETA(DisplayName = "Select Face")
};
