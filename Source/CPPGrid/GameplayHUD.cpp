// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "GameplayWidget.h"
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
	if(GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UGameplayWidget>(GetWorld(), GameplayWidgetClass);
		if (GameplayWidget)
		{
			GameplayWidget->AddToViewport();
		}
	}
	if(PauseWidgetClass)
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
}

void AGameplayHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameplayHUD::UpdateHealthText(int32 NewValue)
{
	if (GameplayWidget)
		GameplayWidget->UpdateHealthText(NewValue);
}

void AGameplayHUD::InitializeTotalHealth(int32 Value)
{
	if (GameplayWidget)
		GameplayWidget->InitializeTotalHealth(Value);
}

bool AGameplayHUD::SwitchGamePause()
{
	if (IsPaused)
	{
		if (PauseWidget && PauseWidget->IsInViewport())
		{
			PauseWidget->RemoveFromViewport();
			if (GameplayWidget && !GameplayWidget->IsInViewport())
			GameplayWidget->AddToViewport();

			IsPaused = false;
		}
	}
	else
	{
		if (GameplayWidget && GameplayWidget->IsInViewport())
		{
			GameplayWidget->RemoveFromViewport();
			if (PauseWidget && !PauseWidget->IsInViewport())
			PauseWidget->AddToViewport();
			
			IsPaused = true;
		}
	}
	return IsPaused;
}