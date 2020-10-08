// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayWidget.h"

UGameplayWidget::UGameplayWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGameplayWidget::UpdateHealthText(int32 NewValue)
{
	HealthText->SetText(FText::FromString(FString::FromInt(NewValue)));
	float BarPercent = ((float)NewValue) / TotalHealth;
	HealthBarLeft->SetPercent(BarPercent);
	HealthBarRight->SetPercent(BarPercent);
}

void UGameplayWidget::InitializeTotalHealth(int32 Value)
{
	TotalHealth = (float)Value;
	UpdateHealthText(Value);
}

void UGameplayWidget::SetBlueKey(bool Held)
{
	if (Held)
		KeyBlue->SetBrushFromTexture(TBlueKey);
	else
		KeyBlue->SetBrushFromTexture(TWhiteKey);
}

void UGameplayWidget::SetGreenKey(bool Held)
{
	if (Held)
		KeyGreen->SetBrushFromTexture(TGreenKey);
	else
		KeyGreen->SetBrushFromTexture(TWhiteKey);
}

void UGameplayWidget::SetPinkKey(bool Held)
{
	if (Held)
		KeyPink->SetBrushFromTexture(TPinkKey);
	else
		KeyPink->SetBrushFromTexture(TWhiteKey);
}