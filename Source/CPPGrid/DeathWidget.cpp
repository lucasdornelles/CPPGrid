// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathWidget.h"
#include "HeroController.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/UMG.h"

UDeathWidget::UDeathWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDeathWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind functionality to UMG buttons
	if (!ContinueB->OnClicked.IsBound())
		ContinueB->OnClicked.AddDynamic(this, &UDeathWidget::CContinue);

	if (!MainMenuB->OnClicked.IsBound())
		MainMenuB->OnClicked.AddDynamic(this, &UDeathWidget::CMainMenu);

	if (!ExitGameB->OnClicked.IsBound())
		ExitGameB->OnClicked.AddDynamic(this, &UDeathWidget::CExitGame);

	bIsFocusable = true;

}

void UDeathWidget::CContinue()
{
	OnContinue.Broadcast();
	return;
}

void UDeathWidget::CMainMenu()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "00MainMenu");
	}
}

void UDeathWidget::CExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}

