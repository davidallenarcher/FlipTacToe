// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToePlayerState.h"

AFlipTacToePlayerState::AFlipTacToePlayerState() : APlayerState()
{
}

AFlipTacToePiece* AFlipTacToePlayerState::GetPiece()
{
	AFlipTacToePiece* NewPiece = nullptr;
	float Angle = FMath::RandRange(0, 3) * 90.0f;
	if (Pieces.Num() < 8) {
		NewPiece = GetWorld()->SpawnActor<AFlipTacToePiece>(PieceClass, FVector(), FRotator(0, Angle, 0));
		Pieces.Add(NewPiece);
	}
	return NewPiece;
}

void AFlipTacToePlayerState::SetImageTexture(UTexture* Texture)
{
	PieceMaterial->SetTextureParameterValue("Image", ImageTexture);
	SpaceMaterial->SetTextureParameterValue("Image", ImageTexture);
}

void AFlipTacToePlayerState::SetBaseColor(FLinearColor Color)
{
	BaseColor = Color;
	PieceMaterial->SetVectorParameterValue("BaseColor", BaseColor);
	SpaceMaterial->SetVectorParameterValue("BaseColor", BaseColor);
}

void AFlipTacToePlayerState::SetHeadsColor(FLinearColor Color)
{
	HeadsColor = Color;
	PieceMaterial->SetVectorParameterValue("HeadsColor", HeadsColor);
	SpaceMaterial->SetVectorParameterValue("HeadsColor", HeadsColor);
}

void AFlipTacToePlayerState::SetTailsColor(FLinearColor Color)
{
	TailsColor = Color;
	PieceMaterial->SetVectorParameterValue("TailsColor", TailsColor);
	SpaceMaterial->SetVectorParameterValue("TailsColor", TailsColor);
}

UMaterialInstance* AFlipTacToePlayerState::GetPieceMaterial()
{
	return PieceMaterial;
}

UMaterialInstance* AFlipTacToePlayerState::GetSpaceMaterial()
{
	return SpaceMaterial;
}
