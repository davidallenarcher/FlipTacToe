// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/GamePiece.h"

#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogGamePiece)

AGamePiece::AGamePiece()
{
 	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	CenterOfRotation = CreateDefaultSubobject<USceneComponent>(FName("CenterOfRotation"));
	CenterOfRotation->SetupAttachment(DefaultRoot);
	PieceMeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(FName("PieceMesh"));
	if (PieceMeshComponent)
	{
		PieceMeshComponent->SetupAttachment(CenterOfRotation);
		PieceMeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
		//PieceMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

AGamePiece::~AGamePiece()
{
}

void AGamePiece::BeginPlay()
{
	Super::BeginPlay();
	//SetReplicateMovement(true);
	//*
	if (MaterialInstanceParent)
	{
		MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialInstanceParent, GetWorld());
		if (MaterialInstanceDynamic)
		{
			PieceMeshComponent->SetMaterial(0, MaterialInstanceDynamic);
			MaterialInstanceDynamic->SetVectorParameterValue(FName("BaseColor"), BaseColor);
			MaterialInstanceDynamic->SetVectorParameterValue(FName("HeadsColor"), HeadsColor);
			MaterialInstanceDynamic->SetVectorParameterValue(FName("TailsColor"), TailsColor);
			MaterialInstanceDynamic->SetTextureParameterValue(FName("Icon"), IconTexture);
		}
	}
	//*/
}

void AGamePiece::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGamePiece, BaseColor);
}

int32 AGamePiece::GetPlayerIndex() const
{
	return PlayerIndex;
}

void AGamePiece::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

PieceFace AGamePiece::GetFace() const
{
	return
		(GetActorUpVector().Z > 0)?
			PieceFace::Heads:
			PieceFace::Tails;
}

void AGamePiece::SetBaseColor(FLinearColor NewBaseColor)
{
	BaseColor = NewBaseColor;
	MaterialInstanceDynamic->SetVectorParameterValue(FName("BaseColor"), BaseColor);
}

void AGamePiece::RepBaseColor()
{
	if (MaterialInstanceDynamic)
	{
		MaterialInstanceDynamic->SetVectorParameterValue(FName("BaseColor"), BaseColor);
	}
}
