// David Allen Archer


#include "FlipTacToePlayer.h"

// Sets default values
UFlipTacToePlayer::UFlipTacToePlayer()
{
	PieceMaterial = UMaterialInstanceDynamic::Create(ParentPieceMaterial, nullptr);
	SpaceMaterial = UMaterialInstanceDynamic::Create(ParentSpaceMaterial, nullptr);
}

/**
* TODO add input parameter to rotate the piece on the z-axis
*/
AFlipTacToePiece* UFlipTacToePlayer::GetPiece()
{
	AFlipTacToePiece* NewPiece = nullptr;
	float Angle = FMath::RandRange(0, 3) * 90.0f;
	if (Pieces.Num() < 8) {
		NewPiece = GetWorld()->SpawnActor<AFlipTacToePiece>(PieceClass, FVector(), FRotator(0, Angle, 0));
		Pieces.Add(NewPiece);
	}
	return NewPiece;
}

void UFlipTacToePlayer::SetImageTexture(UTexture* Texture)
{
	PieceMaterial->SetTextureParameterValue("Image", ImageTexture);
	SpaceMaterial->SetTextureParameterValue("Image", ImageTexture);
}

void UFlipTacToePlayer::SetBaseColor(FLinearColor Color)
{
	PieceMaterial->SetVectorParameterValue("BaseColor", Color);
	SpaceMaterial->SetVectorParameterValue("BaseColor", Color);
}

void UFlipTacToePlayer::SetHeadsColor(FLinearColor Color)
{
	PieceMaterial->SetVectorParameterValue("HeadsColor", Color);
	SpaceMaterial->SetVectorParameterValue("HeadsColor", Color);
}

void UFlipTacToePlayer::SetTailsColor(FLinearColor Color)
{
	PieceMaterial->SetVectorParameterValue("TailsColor", Color);
	SpaceMaterial->SetVectorParameterValue("TailsColor", Color);
}

UMaterialInstance* UFlipTacToePlayer::GetPieceMaterial()
{
	return PieceMaterial;
}

UMaterialInstance* UFlipTacToePlayer::GetSpaceMaterial()
{
	return SpaceMaterial;
}
