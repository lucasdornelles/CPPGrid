// Fill out your copyright notice in the Description page of Project Settings.


#include "BossLevelGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

void ABossLevelGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ABossLevelGameMode::ChangeLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("LevelChange!!"));

	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "02Boss");
	}
}