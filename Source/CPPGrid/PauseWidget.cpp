// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Runtime/UMG/Public/UMG.h"


UPauseWidget::UPauseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ReturnToGameB->OnClicked.IsBound())
		ReturnToGameB->OnClicked.AddDynamic(this, &UPauseWidget::CReturnToGame);
}

void UPauseWidget::CReturnToGame()
{
	return;
}