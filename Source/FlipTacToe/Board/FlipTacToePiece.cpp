// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipTacToePiece.h"

AFlipTacToePiece::AFlipTacToePiece() 
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AFlipTacToePiece::SetOwner(UFlipTacToePlayer* Player)
{
	bool result = false;
	if (Owner == nullptr && Player != nullptr) {
		Owner = Player;
		result = true;
	}
	return result;
}

FlipTacToeFace AFlipTacToePiece::GetShownFace()
{
	return ShownFace;
}

void AFlipTacToePiece::SetShownFace(FlipTacToeFace NewFace)
{
	ShownFace = NewFace;
}

FlipTacToeFace AFlipTacToePiece::FlipFace()
{
	if (ShownFace == FlipTacToeFace::HEADS) {
		SetShownFace(FlipTacToeFace::TAILS);
	} else {
		SetShownFace(FlipTacToeFace::HEADS);
	}
	return ShownFace;
}
