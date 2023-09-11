// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChangeColorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UChangeColorInterface : public UInterface
{
	GENERATED_BODY()
};


class CUBESTEST_API IChangeColorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetNewMaterial(UMaterialInterface* NewMaterial, AActor* CauserActor);

	UFUNCTION(BlueprintNativeEvent)
	void SetBaseMaterial();
};
