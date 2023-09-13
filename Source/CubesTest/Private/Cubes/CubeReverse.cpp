// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubes/CubeReverse.h"
#include "Player/MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/CubesGM.h"

void ACubeReverse::SetNewMaterial_Implementation(UMaterialInterface* NewMaterial, AActor* CauserActor)
{
	auto Player = Cast<AMainPlayer>(CauserActor);

	if (CauserActor != Player && CauserActor != this) return;
	
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
	if (Player)
	{
		Player->Reverse = Player->Reverse * (-1.f);
		if (GEngine)
		{
			FString CubeCount = FString::Printf(TEXT("CurrentCubeCount %d"), Player->ImpulseForce);
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, CubeCount);
		}
	}
}