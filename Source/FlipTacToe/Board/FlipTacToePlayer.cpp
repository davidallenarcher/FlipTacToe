// David Allen Archer


#include "FlipTacToePlayer.h"

// Sets default values
UFlipTacToePlayer::UFlipTacToePlayer()
{
	PieceMaterial = UMaterialInstanceDynamic::Create(ParentPieceMaterial, nullptr);
	SpaceMaterial = UMaterialInstanceDynamic::Create(ParentSpaceMaterial, nullptr);
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
