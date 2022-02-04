// David Allen Archer

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture.h"
#include "FlipTacToePiece.h"
#include "FlipTacToePlayer.generated.h"

UCLASS()
class FLIPTACTOE_API UFlipTacToePlayer : public UObject
{
	GENERATED_BODY()
public:	
	UFlipTacToePlayer();
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UMaterial* ParentPieceMaterial;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UMaterial* ParentSpaceMaterial;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AFlipTacToePiece> PieceClass;
	
	UFUNCTION(BlueprintCallable, Category = "Pieces")
	AFlipTacToePiece* GetPiece();

	UFUNCTION(BlueprintCallable, Category = "Input Parameters")
	void SetImageTexture(UTexture* Texture);
	UFUNCTION(BlueprintCallable, Category = "Input Parameters")
	void SetBaseColor(FLinearColor Color);
	UFUNCTION(BlueprintCallable, Category = "Input Parameters")
	void SetHeadsColor(FLinearColor Color);
	UFUNCTION(BlueprintCallable, Category = "Input Parameters")
	void SetTailsColor(FLinearColor Color);

	UFUNCTION(BlueprintCallable, Category = "Materials")
	UMaterialInstance* GetPieceMaterial();
	UFUNCTION(BlueprintCallable, Category = "Materials")
	UMaterialInstance* GetSpaceMaterial();
private:
	UPROPERTY()
	UTexture* ImageTexture;
	UPROPERTY()
	FLinearColor BaseColor;
	UPROPERTY()
	FLinearColor HeadsColor;
	UPROPERTY()
	FLinearColor TailsColor;
	UPROPERTY()
	UMaterialInstanceDynamic* PieceMaterial;
	UPROPERTY()
	UMaterialInstanceDynamic* SpaceMaterial;
	UPROPERTY()
	TArray<AFlipTacToePiece*> Pieces;
};
