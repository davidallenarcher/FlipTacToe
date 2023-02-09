#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class GamePhase : uint8
{
	GameNotStarted UMETA(DisplayName = "Game not started"),
	GameStarted UMETA(DisplayName = "Game started"),
	GameOver UMETA(DisplayName = "Game over")
};
