// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/ChangeColorInterface.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxCollision"));
	RootComponent = BaseMesh;
	BaseMesh->SetSimulatePhysics(true);
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	check(BaseMesh);

	BaseMesh->OnComponentHit.AddDynamic(this, &AMainPlayer::OnHit);
}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);

	PlayerInputComponent->BindAxis("lookUp", this, &AMainPlayer::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AMainPlayer::LookRight);
}

void AMainPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->ImplementsInterface(UChangeColorInterface::StaticClass()))
	{
		IChangeColorInterface::Execute_SetNewMaterial(OtherActor, BaseMaterial, this);
	}
}

void AMainPlayer::MoveForward(float Value)
{
	FVector Impulse = UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)) * ImpulseForce * Value;

	BaseMesh->AddImpulse(Impulse, NAME_None, true);
}

void AMainPlayer::MoveRight(float Value)
{
	FVector Impulse = UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)) * ImpulseForce * Value;

	BaseMesh->AddImpulse(Impulse, NAME_None, true);
}

void AMainPlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMainPlayer::LookRight(float Value)
{
	AddControllerYawInput(Value);
}
