// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubes/BaseCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Interfaces/ChangeColorInterface.h"
#include "GameModes/CubesGM.h"
#include "Kismet/GameplayStatics.h"


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

void ABaseCube::SetNewMaterial_Implementation(UMaterialInterface* NewMaterial, AActor* CauserActor)
{
	if (CurrentMaterial == NewMaterial) return;

    CurrentMaterial = NewMaterial;
	BaseMesh->SetMaterial(0, CurrentMaterial);

	if (CauserActor == this) return;
	auto CurrentGM = Cast<ACubesGM>(GetWorld()->GetAuthGameMode());
	if (CurrentGM)
	{
		CurrentGM->IncreaseCubeCount();
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound01, GetActorLocation());
}

void ABaseCube::SetBaseMaterial_Implementation()
{
	if (CurrentMaterial == BaseMaterial) return;
	CurrentMaterial = BaseMaterial;
	BaseMesh->SetMaterial(0, CurrentMaterial);

	auto CurrentGM = Cast<ACubesGM>(GetWorld()->GetAuthGameMode());
	if (CurrentGM)
	{
		CurrentGM->DecreaseCubeCount();
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound02, GetActorLocation());
}
