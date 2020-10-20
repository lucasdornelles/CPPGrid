// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CheckpointPawn.h"
#include "HeroCharacter.h"
#include "HeroController.h"
#include "GameplayHUD.h"
#include "DeathWidget.h"
#include "EnemyActor.h"
#include "TotemActor.h"
#include "LevelPortalActor.h"
#include "Engine.h"

void AGameplayGameMode::BeginPlay()
{
	// GetPlayerCharacter and try to cast it to AHeroCharacter
	UWorld* World = GetWorld();
	if (World)
	{
		AHeroCharacter*  PlayerPointer = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
		if (PlayerPointer)
		{
			// If it succeds set player character reference
			PlayerCharacter = PlayerPointer;
			// And bind PlayerCharacterDeath event to listem to player death
			PlayerCharacter->PlayerDeath.AddDynamic(this, &AGameplayGameMode::PlayerCharacterDeath);
			PlayerCharacter->OnInteract.AddDynamic(this, &AGameplayGameMode::ResolveInteract);
		}

		ALevelPortalActor* LevelPortal = Cast<ALevelPortalActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelPortalActor::StaticClass()));
		if (LevelPortal)
		{
			LevelPortal->PortalOverlapEvent.AddDynamic(this, &AGameplayGameMode::ChangeLevel);
		}
	}
}

void AGameplayGameMode::PossesCheckpoint()
{
	APawn* CheckpointPawn = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ACheckpointPawn::StaticClass()));
	if (CheckpointPawn)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			AHeroController* HeroController = Cast<AHeroController>(UGameplayStatics::GetPlayerController(World, 0));
			if (HeroController)
			{
				HeroController->Possess(CheckpointPawn);
				HeroController->ShowDeathMenu();
				AGameplayHUD* GameplayHUD = Cast<AGameplayHUD>(HeroController->GetHUD());
				if (GameplayHUD)
				{
					if (!GameplayHUD->GetDeathWidget()->OnContinue.IsBound())
					{
						GameplayHUD->GetDeathWidget()->OnContinue.AddDynamic(this, &AGameplayGameMode::RestartGame);
					}
				}
			}
		}
	}

}

void AGameplayGameMode::StopEnemyFire()
{
	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), ActorArray);
	for (AActor* TActor : ActorArray)
	{
		AEnemyActor* EnemyActor = Cast<AEnemyActor>(TActor);
		if (EnemyActor)
		{
			EnemyActor->ResetEnemy();
		}
	}
}

void AGameplayGameMode::PlayerCharacterDeath()
{
	PlayerCharacter->SetActorHiddenInGame(true);
	StopEnemyFire();
	PossesCheckpoint();
	
}

void AGameplayGameMode::RestartGame()
{
	PossesPlayerCharacter();
}

void AGameplayGameMode::PossesPlayerCharacter()
{
	
	UWorld* World = GetWorld();
	if (World)
	{
		AHeroController* HeroController = Cast<AHeroController>(UGameplayStatics::GetPlayerController(World, 0));
		if (HeroController)
		{
			HeroController->Possess(PlayerCharacter);
			PlayerCharacter->SetActorHiddenInGame(false);
			//reset player character stats and position, remove death menu, add gameplay menu

			APawn* CheckpointPawn = Cast<APawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ACheckpointPawn::StaticClass()));
			if (CheckpointPawn)
			{
				PlayerCharacter->SetActorLocationAndRotation(
				CheckpointPawn->GetActorLocation(),CheckpointPawn->GetActorQuat());
				PlayerCharacter->GetController()->SetControlRotation(CheckpointPawn->GetActorRotation());
				HeroController->ShowGameplayMenu();
				PlayerCharacter->ResetCharacter();
			}
		}
	}
}

void AGameplayGameMode::ResolveInteract(EInteractableType InteractType)
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

void AGameplayGameMode::ChangeLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("LevelChange!!"));

	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "02Boss");
	}
}