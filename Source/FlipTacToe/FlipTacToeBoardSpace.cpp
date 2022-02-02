// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToeBoardSpace.h"

AFlipTacToeBoardSpace::AFlipTacToeBoardSpace()
{
	PrimaryActorTick.bCanEverTick = false;
}

AFlipTacToePiece* AFlipTacToeBoardSpace::GetCurrentPiece()
{
	return CurrentPiece;
}

AFlipTacToePiece* AFlipTacToeBoardSpace::RemovePiece()
{
	AFlipTacToePiece* RemovedPiece = CurrentPiece;
	CurrentPiece = nullptr;
	return CurrentPiece;
}

bool AFlipTacToeBoardSpace::IsEmpty()
{
	return GetCurrentPiece() == nullptr;
}

bool AFlipTacToeBoardSpace::SetCurrentPiece(AFlipTacToePiece* NewPiece)
{
	bool result = false;
	if (IsEmpty()) {
		CurrentPiece = NewPiece;
		NewPiece->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		NewPiece->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		NewPiece->AttachToComponent(PieceCenterOfRotation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		result = true;
	}
	return result;
}


