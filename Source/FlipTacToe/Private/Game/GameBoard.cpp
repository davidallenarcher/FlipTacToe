// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameBoard.h"

#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogGameBoard);

AGameBoard::AGameBoard(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	Pieces.Init(nullptr, 16);
}

AGameBoard::~AGameBoard()
{
}

void AGameBoard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGameBoard, Pieces);
}

bool AGameBoard::IsValidSpace(FGameCoordinate GameCoordinate)
{
	return GameCoordinate.column >= 0
		&& GameCoordinate.column <= 3
		&& GameCoordinate.row >= 0
		&& GameCoordinate.row <= 3;
}

int32 AGameBoard::GetIndexForSpace(FGameCoordinate GameCoordinate)
{
	return (GameCoordinate.column * 4) + GameCoordinate.row;
}

bool AGameBoard::IsEmptySpace(FGameCoordinate GameCoordinate)
{
	if (IsValidSpace(GameCoordinate))
	{
		return Pieces[GetIndexForSpace(GameCoordinate)] == nullptr;
	}
	return false;
}

void AGameBoard::GetPieceAtSpace(FGameCoordinate GameCoordinate, AGamePiece*& GamePiece)
{
	GamePiece = Pieces[GetIndexForSpace(GameCoordinate)];
}

void AGameBoard::CanPerformMove(FGameCoordinate SourceSpace, FGameCoordinate DestinationSpace, bool& CanPerform)
{
	TArray<FGameCoordinate> AdjacentSpaces;
	GetAvailableFlipSpaces(SourceSpace, AdjacentSpaces);
	if (AdjacentSpaces.Contains(DestinationSpace))
	{
		CanPerform = Pieces[GetIndexForSpace(SourceSpace)] != nullptr;
	}
	else
	{
		CanPerform = false;
	}
}

void AGameBoard::GetSpacesWithFlippablePieces(int32 PlayerIndex, TArray<FGameCoordinate>& FlippableSpaces)
{
	for (int Column = 0; Column <= 3; Column++)
	{
		for (int Row = 0; Row <= 3; Row++)
		{
			FGameCoordinate GameCoordinate = FGameCoordinate(Column, Row);
			if (IsValidSpace(GameCoordinate))
			{
				const AGamePiece* GamePiece = Pieces[GetIndexForSpace(GameCoordinate)];
				if (GamePiece != nullptr && GamePiece->PlayerIndex != PlayerIndex)
				{
					TArray<FGameCoordinate> AvailableSpaces;
					GetAvailableFlipSpaces(GameCoordinate, AvailableSpaces);
					if (AvailableSpaces.Num() > 0)
					{
						FlippableSpaces.Add(GameCoordinate);
					}
				}
			}
		}
	}
}

void AGameBoard::GetAvailableFlipSpaces(FGameCoordinate SourceSpace, TArray<FGameCoordinate>& AvailableSpaces)
{
	if (IsValidSpace(SourceSpace))
	{
		FGameCoordinate DestinationSpace = FGameCoordinate(SourceSpace.column+1, SourceSpace.row);
		if (IsEmptySpace(DestinationSpace))
			AvailableSpaces.Add(DestinationSpace);
		DestinationSpace = FGameCoordinate(SourceSpace.column-1, SourceSpace.row);
		if (IsEmptySpace(DestinationSpace))
			AvailableSpaces.Add(DestinationSpace);
		DestinationSpace = FGameCoordinate(SourceSpace.column, SourceSpace.row+1);
		if (IsEmptySpace(DestinationSpace))
			AvailableSpaces.Add(DestinationSpace);
		DestinationSpace = FGameCoordinate(SourceSpace.column, SourceSpace.row-1);
		if (IsEmptySpace(DestinationSpace))
			AvailableSpaces.Add(DestinationSpace);
	}
}

void AGameBoard::GetEmptySpaces(TArray<FGameCoordinate>& EmptySpaces)
{
	for (int Column = 0; Column <= 3; Column++)
	{
		for (int Row = 0; Row <= 3; Row++)
		{
			FGameCoordinate GameCoordinate = FGameCoordinate(Column, Row);
			if (IsEmptySpace(GameCoordinate))
			{
				EmptySpaces.Add(GameCoordinate);
			}
		}
	}
}

void AGameBoard::FlipPiece(FGameCoordinate SourceSpace, FGameCoordinate DestinationSpace)
{
	const int32 SourceIndex = GetIndexForSpace(SourceSpace);
	const int32 DestinationIndex = GetIndexForSpace(DestinationSpace);
	Pieces[DestinationIndex] = Pieces[SourceIndex];
	FRotator Rotator = Pieces[DestinationIndex]->GetActorRotation();
	Rotator.Roll += 180;
	Pieces[DestinationIndex]->SetActorRotation(Rotator);
	Pieces[SourceIndex] = nullptr;
}

void AGameBoard::PlacePiece(FGameCoordinate DestinationSpace, int32 PlayerIndex, PieceFace ShownFace)
{
	if (IsValidSpace(DestinationSpace))
	{
		Pieces[GetIndexForSpace(DestinationSpace)] = nullptr; // TODO create piece or pass piece as a reference pointer
	}
}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
}
