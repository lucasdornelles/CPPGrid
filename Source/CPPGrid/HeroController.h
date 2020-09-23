// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroController.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API AHeroController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

public:
	UFUNCTION()
	void SwitchPause();

	UFUNCTION()
	void ShowDeathMenu();

private:
	bool IsGamePaused;

};
