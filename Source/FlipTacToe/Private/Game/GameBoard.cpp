// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameBoard.h"

#include "Engine/MyGameState.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogGameBoard);

AGameBoard::AGameBoard(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	BoardState.Init(FPieceInfo(-1, PieceFace::Heads), 16);
}

AGameBoard::~AGameBoard()
{
}

void AGameBoard::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameBoard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGameBoard, BoardState);
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
		return BoardState[GetIndexForSpace(GameCoordinate)].IsEmpty();
	}
	return false;
}

void AGameBoard::GetPieceInfoAtSpace(FGameCoordinate GameCoordinate, bool& IsValid, bool& IsEmpty, int32& PlayerIndex, bool& HeadsShown)
{
	IsValid = IsValidSpace(GameCoordinate);
	if (IsValid)
	{
		const FPieceInfo PieceInfo = BoardState[GetIndexForSpace(GameCoordinate)];
		IsEmpty = PieceInfo.IsEmpty();
		if (!IsEmpty)
		{
			PlayerIndex = PieceInfo.IsEmpty();
			HeadsShown = PieceInfo.IsHeadsShown();
		}
	}
}

void AGameBoard::CanPerformMove(FGameCoordinate SourceSpace, FGameCoordinate DestinationSpace, bool& CanPerform)
{
	TArray<FGameCoordinate> AdjacentSpaces;
	/* Incidentally also checks to see if the spaces are valid */
	GetAvailableFlipSpaces(SourceSpace, AdjacentSpaces);
	if (AdjacentSpaces.Contains(DestinationSpace))
	{
		const FPieceInfo SourcePieceInfo = BoardState[GetIndexForSpace(SourceSpace)];
		const FPieceInfo DestinationPieceInfo = BoardState[GetIndexForSpace(DestinationSpace)];
		CanPerform = (DestinationPieceInfo.IsEmpty()
			&& !SourcePieceInfo.IsEmpty()
			&& SourcePieceInfo.PlayerIndex == GameState->ActivePlayerIndex);
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
				FPieceInfo PieceInfo = BoardState[GetIndexForSpace(GameCoordinate)];
				if (!PieceInfo.IsEmpty() && PieceInfo.PlayerIndex != PlayerIndex)
				{
					FlippableSpaces.Add(GameCoordinate);					
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
	if (HasAuthority())
	{
		BoardState[GetIndexForSpace(DestinationSpace)].PlayerIndex = BoardState[GetIndexForSpace(SourceSpace)].PlayerIndex;
		if (BoardState[GetIndexForSpace(SourceSpace)].IsHeadsShown())
		{
			BoardState[GetIndexForSpace(DestinationSpace)].ShownFace = PieceFace::Tails;
		} 
		else
		{
			BoardState[GetIndexForSpace(DestinationSpace)].ShownFace = PieceFace::Heads;
		}
		BoardState[GetIndexForSpace(SourceSpace)].PlayerIndex = -1;
	} else
	{
		UE_LOG(LogGameBoard, Warning, TEXT("FlipPiece[%d]: Without Authority"), GameState->GetActivePlayerIndex())
	}
}

void AGameBoard::PlacePiece(FGameCoordinate DestinationSpace, int32 PlayerIndex, PieceFace ShownFace)
{
	if (IsValidSpace(DestinationSpace))
	{
		BoardState[GetIndexForSpace(DestinationSpace)].PlayerIndex = PlayerIndex;
		BoardState[GetIndexForSpace(DestinationSpace)].ShownFace = ShownFace;
	}
}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();

	GameState = static_cast<AMyGameState*>(AActor::GetWorld()->GetGameState());
}
