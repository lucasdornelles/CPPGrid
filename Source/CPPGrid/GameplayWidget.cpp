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
}