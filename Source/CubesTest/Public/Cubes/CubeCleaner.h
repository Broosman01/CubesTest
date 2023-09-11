// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cubes/BaseCube.h"
#include "CubeCleaner.generated.h"

UCLASS()
class CUBESTEST_API ACubeCleaner : public ABaseCube
{
	GENERATED_BODY()

public:
	virtual	void SetNewMaterial_Implementation(UMaterialInterface* NewMaterial, AActor* CauserActor) override;

protected:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
