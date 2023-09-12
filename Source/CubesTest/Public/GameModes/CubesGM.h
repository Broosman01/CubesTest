// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Cubes/BaseCube.h"
#include "CubesGM.generated.h"


UCLASS()
class CUBESTEST_API ACubesGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACubesGM();

	void IncreaseCubeCount();
	void DecreaseCubeCount();
	
	UFUNCTION(BlueprintCallable)
	int32 GetCubeCountForWin() const { return CubeCountForWin; }

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentCubeCount() const { return CurrentCubeCount; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> CubeActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> WinWidgetClass;
private:
	int32 CubeCountForWin = 0;
	int32 CurrentCubeCount = 0;

	int32 CalculateCubeCountForWin();

	void CheckWinning();
};
