// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FlipTacToeBoard.h"
#include "FlipTacToeGameState.generated.h"

// Forward Declarations
class AFlipTacToeBoard;
class AFlipTacToePiece;

/**
 * 
 */
UCLASS()
class FLIPTACTOE_API AFlipTacToeGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToeBoard* BoardRef;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	TArray<AFlipTacToePiece*> PiecesRef;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	AFlipTacToePiece* SelectedPieceRef;
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBoardRef();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPiecesRef();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void ProcessPiece(AFlipTacToePiece* Piece);

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "References")
	TArray<FFlipTacToePlayer> Players;
};
