// Fill out your copyright notice in the Description page of Project Settings.


#include "CreditsGameMode.h"
#include "TotemActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"

void ACreditsGameMode::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		// Get Totem Actor and activate them

		TArray<AActor*> OutActors;

		UGameplayStatics::GetAllActorsOfClass(this, ATotemActor::StaticClass(), OutActors);

		for (AActor* Actor : OutActors)
		{
			ATotemActor* TotemActor = Cast<ATotemActor>(Actor);
			if (TotemActor)
			{
				TotemActor->ActivateTotem();
			}
		}
	}

	// Play sound if setted on blueprint
	if (SoundBase)
	{
		UGameplayStatics::SpawnSound2D(this, SoundBase);
	}
}

void ACreditsGameMode::ChangeLevel()
{
	//Return to MainMenu level
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "00MainMenu");
	}
}
