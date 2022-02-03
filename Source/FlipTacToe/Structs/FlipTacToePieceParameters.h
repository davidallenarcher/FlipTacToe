// David Allen Archer

#pragma once

#include "CoreMinimal.h"
#include "Materials\MaterialInstance.h"
#include "FlipTacToePieceParameters.generated.h"

USTRUCT(BlueprintType)
struct FLIPTACTOE_API FFlipTacToePieceParameters
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstance* PieceMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLinearColor BaseColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLinearColor HeadsColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLinearColor TailsColor;
};
