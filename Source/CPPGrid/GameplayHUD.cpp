// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"

AGameplayHUD::AGameplayHUD()
{

}

void AGameplayHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameplayHUD::BeginPlay()
{
	if(GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UGameplayWidget>(GetWorld(), GameplayWidgetClass);
		if (GameplayWidget)
		{
			GameplayWidget->AddToViewport();
		}
		
	}
}

void AGameplayHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameplayHUD::UpdateHealthText(int32 NewValue)
{
	if (GameplayWidget)
	{
		GameplayWidget->UpdateHealthText(NewValue);
	}
}