// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/PieceFace.h"
#include "GameFramework/Actor.h"
#include "GamePiece.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGamePiece, Log, All);

UCLASS()
class FLIPTACTOE_API AGamePiece : public AActor
{
	GENERATED_BODY()
	
public:	
	AGamePiece();
	virtual ~AGamePiece() override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* DefaultRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* CenterOfRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* PieceMeshComponent;
	
	UFUNCTION(BlueprintGetter)
	int32 GetPlayerIndex() const;
	UFUNCTION(BlueprintSetter)
	void SetPlayerIndex(int32 NewPlayerIndex);
	
	UFUNCTION(BlueprintPure)
	PieceFace GetFace() const;
	
	UPROPERTY(BlueprintGetter = GetPlayerIndex, BlueprintSetter = SetPlayerIndex, meta=(ExposeOnSpawn=true))
	int32 PlayerIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UMaterial* MaterialInstanceParent;

	UFUNCTION(BlueprintSetter)
	void SetBaseColor(FLinearColor NewBaseColor);

	UFUNCTION()
	void RepBaseColor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetBaseColor, ReplicatedUsing=RepBaseColor, meta=(AllowPrivateAccess = "true"))
	FLinearColor BaseColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	FLinearColor HeadsColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	FLinearColor TailsColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UTexture* IconTexture;
	
private:	
	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic;
};
