// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayerController.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}