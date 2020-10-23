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
		World->GetTimerManager().SetTimer(CountEnemyTimer, this, &ABossLevelGameMode::CountEnemy, 2.0f, true);
		ALevelPortalActor* LevelPortal = Cast<ALevelPortalActor>(UGameplayStatics::GetActorOfClass(World, ALevelPortalActor::StaticClass()));
		if (LevelPortal)
		{
			LevelPortal->PortalOverlapEvent.AddDynamic(this, &ABossLevelGameMode::ChangeLevel);
		}
	}

	
}

void ABossLevelGameMode::ChangeLevel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("GameCleared!"));

	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, "03Credits");
	}
}

void ABossLevelGameMode::RestartGame()
{
	Super::RestartGame();
	
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
				count++;
			}
		}
		if (count == 0)
		{
			if (World->GetTimerManager().IsTimerActive(CountEnemyTimer))
			{
				World->GetTimerManager().ClearTimer(CountEnemyTimer);
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Cleared!!"));
				ALevelPortalActor* LevelPortal = Cast<ALevelPortalActor>(UGameplayStatics::GetActorOfClass(World, ALevelPortalActor::StaticClass()));
				if (LevelPortal)
				{
					LevelPortal->AnimatePortal();
				}
			}
		}
	}
}