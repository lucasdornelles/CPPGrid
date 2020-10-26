// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MenuGameMode.h"

void AMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &AMenuPlayerController::ExitGame).bExecuteWhenPaused = true;
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMenuPlayerController::ReturnToMenu).bExecuteWhenPaused = true;
}

void AMenuPlayerController::ExitGame()
{
	AMenuGameMode* GameMode = Cast<AMenuGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->ExitGame();
	}

}

void AMenuPlayerController::ReturnToMenu()
{
	AMenuGameMode* GameMode = Cast<AMenuGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->ChangeLevel();
	}
}