// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (SoundBase)
	{
		UGameplayStatics::SpawnSound2D(this, SoundBase);
	}
}

void AMainMenuGameMode::ChangeLevel()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "01Gameplay");
	}
}