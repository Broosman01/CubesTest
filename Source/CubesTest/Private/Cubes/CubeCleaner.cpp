// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubes/CubeCleaner.h"
#include "Interfaces/ChangeColorInterface.h"
#include "Player/MainPlayer.h"
#include "Kismet/GameplayStatics.h"

void ACubeCleaner::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsMarked())
	{
		if (OtherActor->GetClass()->ImplementsInterface(UChangeColorInterface::StaticClass()))
		{
			IChangeColorInterface::Execute_SetNewMaterial(OtherActor, CurrentMaterial, this);
		}
	}
	else
	{
		if (OtherActor->GetClass()->ImplementsInterface(UChangeColorInterface::StaticClass()))
		{
			IChangeColorInterface::Execute_SetBaseMaterial(OtherActor);
		}
	}
}

void ACubeCleaner::SetNewMaterial_Implementation(UMaterialInterface* NewMaterial, AActor* Causer)
{
	auto Player = Cast<AMainPlayer>(Causer);

	if (Causer != Player && Causer != this) return;

	Super::SetNewMaterial_Implementation(NewMaterial, Causer);
}