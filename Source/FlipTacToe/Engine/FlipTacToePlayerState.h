// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../Board/FlipTacToePiece.h"
#include "FlipTacToePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API AFlipTacToePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<AFlipTacToePiece> PieceClass = AFlipTacToePiece::StaticClass();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Materials", meta = (ExposeOnSpawn = "true"))
	UMaterial* ParentPieceMaterial;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Materials", meta = (ExposeOnSpawn = "true"))
	UMaterial* ParentSpaceMaterial;
public:
	AFlipTacToePlayerState();
public:
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
