// Fill out your copyright notice in the Description page of Project Settings.
//Q: Would experience in developing tools for numerical simulation research help me when aplying to a programmer position?

#include "CreditsPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "CreditsGameMode.h"

void ACreditsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &ACreditsPlayerController::ExitGame).bExecuteWhenPaused = true;
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACreditsPlayerController::ReturnToMenu).bExecuteWhenPaused = true;
}

void ACreditsPlayerController::ExitGame()
{
	ACreditsGameMode* GameMode = Cast<ACreditsGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->ExitGame();
	}

}

void ACreditsPlayerController::ReturnToMenu()
{
	ACreditsGameMode* GameMode = Cast<ACreditsGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->ChangeLevel();
	}
}