// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubes/BaseCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Interfaces/ChangeColorInterface.h"

ABaseCube::ABaseCube()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxCollision"));
	RootComponent = BaseMesh;
}

void ABaseCube::BeginPlay()
{
	Super::BeginPlay();

	check(BaseMesh);
	SetNewMaterial_Implementation(BaseMaterial, this);

	BaseMesh->OnComponentHit.AddDynamic(this, &ABaseCube::OnHit);

	GetWorld()->GetTimerManager().SetTimer(ImpulseTimer, this, &ABaseCube::AddRandomMovement, 0.75f, true);
}

void ABaseCube::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsMarked()) return;

	if (OtherActor->GetClass()->ImplementsInterface(UChangeColorInterface::StaticClass()))
	{
		IChangeColorInterface::Execute_SetNewMaterial(OtherActor, CurrentMaterial, this);
	}
}

void ABaseCube::AddRandomMovement()
{
	FVector ImpulseInDegrees = ImpulseInDegreesForce * FMath::VRand();
	FVector Impulse = ImpulseForce * FMath::VRand();

	BaseMesh->AddImpulse(Impulse * 100, NAME_None, true);
	BaseMesh->AddAngularImpulseInDegrees(ImpulseInDegrees * 100, NAME_None, true);
}

void ABaseCube::SetNewMaterial_Implementation(UMaterialInterface* NewMaterial, AActor* Causer)
{
	if (CurrentMaterial == NewMaterial) return;

    CurrentMaterial = NewMaterial;
	BaseMesh->SetMaterial(0, CurrentMaterial);
}

void ABaseCube::SetBaseMaterial_Implementation()
{
	CurrentMaterial = BaseMaterial;
	BaseMesh->SetMaterial(0, CurrentMaterial);
}
