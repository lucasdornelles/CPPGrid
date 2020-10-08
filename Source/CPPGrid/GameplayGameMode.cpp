// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CheckpointPawn.h"
#include "HeroCharacter.h"
#include "HeroController.h"
#include "GameplayHUD.h"
#include "DeathWidget.h"
#include "EnemyActor.h"
#include "Engine.h"

void AGameplayGameMode::BeginPlay()
{
	// GetPlayerCharacter and try to cast it to AHeroCharacter
	UWorld* World = GetWorld();
	if (World)
	{
		AHeroCharacter*  PlayerPointer = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (PlayerPointer)
		{
			// If it succeds set player character reference
			PlayerCharacter = PlayerPointer;
			// And bind PlayerCharacterDeath event to listem to player death
			PlayerCharacter->PlayerDeath.AddDynamic(this, &AGameplayGameMode::PlayerCharacterDeath);
			PlayerCharacter->OnInteract.AddDynamic(this, &AGameplayGameMode::ResolveInteract);
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
				HeroController->ShowGameplayMenu();
				PlayerCharacter->ResetCharacter();
			}
		}
	}
}

void AGameplayGameMode::ResolveInteract(EInteractableType InteractType)
{

	AGameplayHUD* GameplayHUD = nullptr;

	UWorld* World = GetWorld();
	if (World)
	{
		AHeroController* HeroController = Cast<AHeroController>(UGameplayStatics::GetPlayerController(World, 0));
		if (HeroController)
		{
			GameplayHUD = Cast<AGameplayHUD>(HeroController->GetHUD());
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
		if (GameplayHUD)
			GameplayHUD->SetBlueKey(IsHoldingBlueKey);
		break;

	case EInteractableType::GREENKEY:
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Green"));
		if (!IsHoldingGreenKey)
			IsHoldingGreenKey = true;
		if (GameplayHUD)
			GameplayHUD->SetGreenKey(IsHoldingGreenKey);
		break;

	case EInteractableType::PINKKEY:
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Pink"));
		if (!IsHoldingPinkKey)
			IsHoldingPinkKey = true;
		if (GameplayHUD)
			GameplayHUD->SetPinkKey(IsHoldingPinkKey);
		break;

	case EInteractableType::BLUETOTEM:
		break;

	case EInteractableType::GREENTOTEM:
		break;

	case EInteractableType::PINKTOTEM:
		break;

	}
}