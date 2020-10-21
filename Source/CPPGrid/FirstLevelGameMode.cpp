// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstLevelGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CheckpointPawn.h"
#include "HeroCharacter.h"
#include "HeroController.h"
#include "GameplayHUD.h"
#include "TotemActor.h"
#include "LevelPortalActor.h"
#include "Engine.h"

void AFirstLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	ALevelPortalActor* LevelPortal = Cast<ALevelPortalActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelPortalActor::StaticClass()));
	if (LevelPortal)
	{
		LevelPortal->PortalOverlapEvent.AddDynamic(this, &AFirstLevelGameMode::ChangeLevel);
	}
}

void AFirstLevelGameMode::ResolveInteract(EInteractableType InteractType)
{

	AGameplayHUD* GameplayHUD = nullptr;
	ATotemActor* BlueTotem = nullptr;
	ATotemActor* GreenTotem = nullptr;
	ATotemActor* PinkTotem = nullptr;
	ALevelPortalActor* LevelPortal = nullptr;

	UWorld* World = GetWorld();
	if (World)
	{
		AHeroController* HeroController = Cast<AHeroController>(UGameplayStatics::GetPlayerController(World, 0));
		if (HeroController)
		{
			GameplayHUD = Cast<AGameplayHUD>(HeroController->GetHUD());
		}

		LevelPortal = Cast<ALevelPortalActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelPortalActor::StaticClass()));

		TArray<AActor*> OutActors;

		UGameplayStatics::GetAllActorsOfClass(this, ATotemActor::StaticClass(), OutActors);

		for (AActor* Actor : OutActors)
		{
			if (!IsValid(BlueTotem) && Actor->Tags.Contains(FName("BLUETOTEM")))
				BlueTotem = Cast<ATotemActor>(Actor);
			else if (!IsValid(GreenTotem) && Actor->Tags.Contains(FName("GREENTOTEM")))
				GreenTotem = Cast<ATotemActor>(Actor);
			else if (!IsValid(PinkTotem) && Actor->Tags.Contains(FName("PINKTOTEM")))
				PinkTotem = Cast<ATotemActor>(Actor);
		}
	}

	switch (InteractType)
	{

	default:
		break;

	case EInteractableType::BLUEKEY:
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Blue"));
		if (!IsHoldingBlueKey)
			IsHoldingBlueKey = true;
		if (IsValid(GameplayHUD))
			GameplayHUD->SetBlueKey(IsHoldingBlueKey);
		break;

	case EInteractableType::GREENKEY:
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Green"));
		if (!IsHoldingGreenKey)
			IsHoldingGreenKey = true;
		if (IsValid(GameplayHUD))
			GameplayHUD->SetGreenKey(IsHoldingGreenKey);
		break;

	case EInteractableType::PINKKEY:
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Pink"));
		if (!IsHoldingPinkKey)
			IsHoldingPinkKey = true;
		if (IsValid(GameplayHUD))
			GameplayHUD->SetPinkKey(IsHoldingPinkKey);
		break;

	case EInteractableType::BLUETOTEM:
		if (IsHoldingBlueKey && !IsActiveBlueTotem)
		{
			if (IsValid(BlueTotem))
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("BlueTotem"));
				IsActiveBlueTotem = true;
				//ResolveTotemActivation
				BlueTotem->ActivateTotem();
				if (IsValid(LevelPortal))
				{
					if (IsActiveBlueTotem && IsActiveGreenTotem && IsActivePinkTotem && !LevelPortal->IsPortalActive)
					{
						LevelPortal->AnimatePortal();
					}
				}
				break;
			}
		}
		break;

	case EInteractableType::GREENTOTEM:
		if (IsHoldingGreenKey && !IsActiveGreenTotem)
		{
			if (IsValid(GreenTotem))
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("GreenTotem"));
				IsActiveGreenTotem = true;
				//ResolveTotemActivation
				GreenTotem->ActivateTotem();
				if (IsValid(LevelPortal))
				{
					if (IsActiveBlueTotem && IsActiveGreenTotem && IsActivePinkTotem && !LevelPortal->IsPortalActive)
					{
						LevelPortal->AnimatePortal();
					}
				}
				break;
			}
		}
		break;

	case EInteractableType::PINKTOTEM:
		if (IsHoldingPinkKey && !IsActivePinkTotem)
		{
			if (IsValid(PinkTotem))
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("PinkTotem"));
				IsActivePinkTotem = true;
				//ResolveTotemActivation
				PinkTotem->ActivateTotem();
				if (IsValid(LevelPortal))
				{
					if (IsActiveBlueTotem && IsActiveGreenTotem && IsActivePinkTotem && !LevelPortal->IsPortalActive)
					{
						LevelPortal->AnimatePortal();
					}
				}
				break;
			}
		}
		break;

	}
}

void AFirstLevelGameMode::ChangeLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("LevelChange!!"));

	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "02Boss");
	}
}