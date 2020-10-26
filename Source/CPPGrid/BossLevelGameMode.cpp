// Fill out your copyright notice in the Description page of Project Settings.


#include "BossLevelGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyActor.h"
#include "LevelPortalActor.h"
#include "Engine.h"

void ABossLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	if (World)
	{
		// Get Enemys on boss level and activate then on a random timer for variability
		TArray<AActor*> ActorArray;
		UGameplayStatics::GetAllActorsOfClass(World, AEnemyActor::StaticClass(), ActorArray);
		for (AActor* TActor : ActorArray)
		{
			AEnemyActor* EnemyActor = Cast<AEnemyActor>(TActor);
			if (EnemyActor)
			{
				EnemyActor->RandomSetPlayerVisible();
			}
		}

		// Set a timer to count enemys to end the level
		World->GetTimerManager().SetTimer(CountEnemyTimer, this, &ABossLevelGameMode::CountEnemy, 2.0f, true);

		// Get the end level portal and bind changelevel to the overlap event
		ALevelPortalActor* LevelPortal = Cast<ALevelPortalActor>(UGameplayStatics::GetActorOfClass(World, ALevelPortalActor::StaticClass()));
		if (LevelPortal)
		{
			LevelPortal->PortalOverlapEvent.AddDynamic(this, &ABossLevelGameMode::ChangeLevel);
		}
	}

	// If SoundBase was setted on the game mode blueprint play it
	if (SoundBase)
	{
		UGameplayStatics::SpawnSound2D(this, SoundBase);
	}
	
}

void ABossLevelGameMode::ChangeLevel()
{
	// Open credits level when overlap with level portal
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "03Credits");
	}
}

void ABossLevelGameMode::RestartGame()
{
	// Call GameplayGameMode::RestartGame()
	Super::RestartGame();
	
	// Reactivate enemys on a random timer
	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), ActorArray);
	for (AActor* TActor : ActorArray)
	{
		AEnemyActor* EnemyActor = Cast<AEnemyActor>(TActor);
		if (EnemyActor)
		{
			EnemyActor->RandomSetPlayerVisible();
		}
	}

}

void ABossLevelGameMode::CountEnemy()
{
	UWorld* World = GetWorld();

	int32 count = 0;

	if (World)
	{
		TArray<AActor*> ActorArray;
		UGameplayStatics::GetAllActorsOfClass(World, AEnemyActor::StaticClass(), ActorArray);
		for (AActor* TActor : ActorArray)
		{
			AEnemyActor* EnemyActor = Cast<AEnemyActor>(TActor);
			if (EnemyActor)
			{
				// If it succed in casting TActor then it is a valid enemy
				// increment enemy count
				count++;
			}
		}
		if (count == 0)
		{
			if (World->GetTimerManager().IsTimerActive(CountEnemyTimer))
			{
				// If enemy count is zero remove enemy counter timer and activate level portal
				World->GetTimerManager().ClearTimer(CountEnemyTimer);
				ALevelPortalActor* LevelPortal = Cast<ALevelPortalActor>(UGameplayStatics::GetActorOfClass(World, ALevelPortalActor::StaticClass()));
				if (LevelPortal)
				{
					LevelPortal->AnimatePortal();
				}
			}
		}
	}
}