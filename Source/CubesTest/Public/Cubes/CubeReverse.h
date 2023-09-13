// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cubes/BaseCube.h"
#include "CubeReverse.generated.h"


UCLASS()
class CUBESTEST_API ACubeReverse : public ABaseCube
{
	GENERATED_BODY()

public:
	virtual void SetNewMaterial_Implementation(UMaterialInterface* NewMaterial, AActor* CauserActor) override;
	
};
