// Fill out your copyright notice in the Description page of Project Settings.


#include "CreditsGameMode.h"
#include "TotemActor.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"

void ACreditsGameMode::BeginPlay()
{
	UWorld* World = GetWorld();
	if (World)
	{
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

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController)
		{
			AActor* CameraActor = UGameplayStatics::GetActorOfClass(this, ACameraActor::StaticClass());
			if (CameraActor)
			{
				PlayerController->SetViewTarget(CameraActor);
			}
			
		}

		if (CreditsWidgetClass)
		{
			CreditsWidget = CreateWidget<UUserWidget>(World, CreditsWidgetClass);
			CreditsWidget->AddToViewport();
		}
	}

	

	
}

void ACreditsGameMode::ChangeLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("BackToMenu..."));

	UWorld* World = GetWorld();
	if (World)
	{
		//UGameplayStatics::OpenLevel(World, "00MainMenu");
	}
}

void ACreditsGameMode::ExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}