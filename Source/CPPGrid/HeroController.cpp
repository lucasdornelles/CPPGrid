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
			bool bHUDPaused = GameplayHUD->SwitchGamePause();
			if (!bHUDPaused)
			{
				bShowMouseCursor = false;
				SetInputMode(FInputModeGameOnly());
				SetPause(bHUDPaused);
			}
		}
		else
		{
			bool bHUDPaused = GameplayHUD->SwitchGamePause();
			if (bHUDPaused)
			{
				FInputModeGameAndUI InputModeSettings;
				InputModeSettings.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				bShowMouseCursor = true;
				InputModeSettings.SetWidgetToFocus(GameplayHUD->GetPauseWidget()->TakeWidget());
				SetInputMode(InputModeSettings);
				SetPause(bHUDPaused);
				GameplayHUD->GetPauseWidget()->SetKeyboardFocus();
			}
		}
	}
}

void AHeroController::ShowDeathMenu()
{
	AGameplayHUD* GameplayHUD = Cast<AGameplayHUD>(GetHUD());
	if (GameplayHUD)
	{
		GameplayHUD->ShowDeathMenu();
		FInputModeGameAndUI InputModeSettings;
		InputModeSettings.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		bShowMouseCursor = true;
		InputModeSettings.SetWidgetToFocus(GameplayHUD->GetDeathWidget()->TakeWidget());
		SetInputMode(InputModeSettings);
	}
}

void AHeroController::ShowGameplayMenu()
{
	AGameplayHUD* GameplayHUD = Cast<AGameplayHUD>(GetHUD());
	if (GameplayHUD)
	{
		FInputModeGameOnly InputModeSettings;
		bShowMouseCursor = false;
		SetInputMode(InputModeSettings);
		GameplayHUD->ShowGameplayMenu();
	}
}