// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "HeroController.h"
#include "Runtime/UMG/Public/UMG.h"


UPauseWidget::UPauseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ReturnToGameB->OnClicked.IsBound())
		ReturnToGameB->OnClicked.AddDynamic(this, &UPauseWidget::CReturnToGame);

	if (!MainMenuB->OnClicked.IsBound())
		MainMenuB->OnClicked.AddDynamic(this, &UPauseWidget::CMainMenu);
	
	if (!ExitGameB->OnClicked.IsBound())
		ExitGameB->OnClicked.AddDynamic(this, &UPauseWidget::CExitGame);

	bIsFocusable = true;

}

void UPauseWidget::CReturnToGame()
{
	AHeroController* HeroController = Cast<AHeroController>(GetOwningPlayer());
	if (HeroController)
	{
		HeroController->SwitchPause();
	}
	return;
}

void UPauseWidget::CMainMenu()
{
	return;
}

void UPauseWidget::CExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}

