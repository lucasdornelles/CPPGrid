// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "GameplayWidget.h"
#include "DeathWidget.h"
#include "PauseWidget.h"

AGameplayHUD::AGameplayHUD()
{

}

void AGameplayHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameplayHUD::BeginPlay()
{
	IsPaused = false;
	// Create HUD widgets and add gameplay widget to viewport
	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UGameplayWidget>(GetWorld(), GameplayWidgetClass);
		if (GameplayWidget)
		{
			GameplayWidget->AddToViewport();
		}
	}
	if (PauseWidgetClass)
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);

	if (DeathWidgetClass)
		DeathWidget = CreateWidget<UDeathWidget>(GetWorld(), DeathWidgetClass);
}

void AGameplayHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameplayHUD::UpdateHealthText(int32 NewValue)
{
	// Pass new health value to gameplay widget
	if (GameplayWidget)
		GameplayWidget->UpdateHealthText(NewValue);
}

void AGameplayHUD::InitializeTotalHealth(int32 Value)
{
	// Pass new health value to gameplay widget
	if (GameplayWidget)
		GameplayWidget->InitializeTotalHealth(Value);
}

bool AGameplayHUD::SwitchGamePause()
{
	if (IsPaused)
	{
		if (PauseWidget && PauseWidget->IsInViewport())
		{
			// If it is paused then should unpause
			// Remove pause widget from viewport and add gameplay widget
			PauseWidget->RemoveFromViewport();
			// most of these checks are not needed but its good to be safe
			if (GameplayWidget && !GameplayWidget->IsInViewport())
			GameplayWidget->AddToViewport();
			
			IsPaused = false;
		}
	}
	else
	{
		if (GameplayWidget && GameplayWidget->IsInViewport())
		{
			// If it is not paused the sould pause
			// Remove gameplay widget from vieport and add pause widget
			GameplayWidget->RemoveFromViewport();
			if (PauseWidget && !PauseWidget->IsInViewport())
				PauseWidget->AddToViewport();
			
			IsPaused = true;
		}
	}
	// return if it paused or unpaused
	return IsPaused;
}

void AGameplayHUD::ShowDeathMenu()
{
	if (GameplayWidget && GameplayWidget->IsInViewport())
	{
		GameplayWidget->RemoveFromViewport();
		if (DeathWidget && !DeathWidget->IsInViewport())
			DeathWidget->AddToViewport();

	}
}

void AGameplayHUD::ShowGameplayMenu()
{
	// called when game restarts
	if (DeathWidget && DeathWidget->IsInViewport())
	{
		DeathWidget->RemoveFromViewport();
		if (GameplayWidget && !GameplayWidget->IsInViewport())
			GameplayWidget->AddToViewport();

	}
}

UPauseWidget* AGameplayHUD::GetPauseWidget()
{
	
	return PauseWidget;

}

UDeathWidget* AGameplayHUD::GetDeathWidget()
{

	return DeathWidget;

}

void AGameplayHUD::SetBlueKey(bool Held)
{
	GameplayWidget->SetBlueKey(Held);
}

void AGameplayHUD::SetGreenKey(bool Held)
{
	GameplayWidget->SetGreenKey(Held);
}

void AGameplayHUD::SetPinkKey(bool Held)
{
	GameplayWidget->SetPinkKey(Held);
}