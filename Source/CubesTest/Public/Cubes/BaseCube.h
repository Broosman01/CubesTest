// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ChangeColorInterface.h"
#include "BaseCube.generated.h"

class UStaticMeshComponent;

DECLARE_MULTICAST_DELEGATE(FAddCube)
DECLARE_MULTICAST_DELEGATE(FRemoveCube)

UCLASS()
class CUBESTEST_API ABaseCube : public AActor, public IChangeColorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCube();

	virtual void SetNewMaterial_Implementation(UMaterialInterface* NewMaterial, AActor* CauserActor);

	void SetBaseMaterial_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseMesh")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1", ClampMax = "10"))
	int32 ImpulseForce = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseMesh", meta = (ClampMin = "1", ClampMax = "10"))
	int32 ImpulseInDegreesForce = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Color")
	UMaterialInterface* BaseMaterial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Color")
	UMaterialInterface* CurrentMaterial;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	bool IsMarked() const { return BaseMaterial != CurrentMaterial; }

private:
	FAddCube AddCube;
	FRemoveCube RemoveCube;

	FTimerHandle ImpulseTimer;

	void AddRandomMovement();
};
