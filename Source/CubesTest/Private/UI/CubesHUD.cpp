// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CubesHUD.h"
#include "Blueprint/UserWidget.h"

void ACubesHUD::BeginPlay()
{
	Super::BeginPlay();

    if (PlayerWidgetClass)
    {
        auto PlayerWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
        PlayerWidget->AddToViewport();
    }
}