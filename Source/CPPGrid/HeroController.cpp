// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroController.h"
#include "GameplayHUD.h"
#include "HeroCharacter.h"

void AHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &AHeroController::SwitchPause).bExecuteWhenPaused = true;
}

void AHeroController::SwitchPause()
{

	AGameplayHUD* GameplayHUD = Cast<AGameplayHUD>(GetHUD());
	if (GameplayHUD)
	{
		if (IsPaused())
		{
			//bool bHUDPaused = GameplayHUD->SwitchGamePause();
			SetPause(GameplayHUD->SwitchGamePause());
		}
		else
		{
			//bool bHUDPaused = GameplayHUD->SwitchGamePause();
			SetPause(GameplayHUD->SwitchGamePause());
		}
	}
}