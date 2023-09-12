// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/CubesGM.h"
#include "Cubes/BaseCube.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void ACubesGM::BeginPlay()
{
    Super::BeginPlay();

    CubeCountForWin = CalculateCubeCountForWin();

    if (GEngine)
    {
        FString CubeCount = FString::Printf(TEXT("CubeCountForWin %d"), CubeCountForWin);
        GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, CubeCount);
    }
    if (GEngine)
    {
        FString CubeCount = FString::Printf(TEXT("CurrentCubeCount %d"), CurrentCubeCount);
        GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, CubeCount);
    }
}

int32 ACubesGM::CalculateCubeCountForWin()
{
    TArray<AActor*> CubeActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), CubeActorClass, CubeActors);

    return CubeActors.Num();
}

void ACubesGM::IncreaseCubeCount()
{
    ++CurrentCubeCount;
    if (GEngine)
    {
        FString CubeCount = FString::Printf(TEXT("CurrentCubeCount %d"), CurrentCubeCount);
        GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, CubeCount);
    }
    CheckWinning();
}

void ACubesGM::DecreaseCubeCount()
{
    --CurrentCubeCount;
    if (GEngine)
    {
        FString CubeCount = FString::Printf(TEXT("CurrentCubeCount %d"), CurrentCubeCount);
        GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, CubeCount);
    }
    CheckWinning();
}

void ACubesGM::CheckWinning()
{
    if (CurrentCubeCount >= CubeCountForWin)
    {
        if (GEngine)
        {
            FString WinString = FString("----YOU WIN----");
            GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Green, WinString);
        }
        if (WinWidgetClass)
        {
            auto WinWidget = CreateWidget<UUserWidget>(GetWorld(), WinWidgetClass);
            WinWidget->AddToViewport();
        }
    }
}
