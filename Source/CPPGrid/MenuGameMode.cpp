// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

void AMenuGameMode::BeginPlay()
{
	UWorld* World = GetWorld();

	if (World)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController)
		{
			AActor* CameraActor = UGameplayStatics::GetActorOfClass(this, ACameraActor::StaticClass());
			if (CameraActor)
			{
				PlayerController->SetViewTarget(CameraActor);
			}

		}

		if (MenuWidgetClass)
		{
			MenuWidget = CreateWidget<UUserWidget>(World, MenuWidgetClass);
			MenuWidget->AddToViewport();
		}
	}
}

void AMenuGameMode::ChangeLevel()
{
	return;
}

void AMenuGameMode::ExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}