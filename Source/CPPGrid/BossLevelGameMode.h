// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayGameMode.h"
#include "Components/TimelineComponent.h"
#include "BossLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API ABossLevelGameMode : public AGameplayGameMode
{
	GENERATED_BODY()

	FTimerHandle CountEnemyTimer;

public:

	virtual void BeginPlay() override;

	virtual void ChangeLevel() override;

	virtual void RestartGame() override;
	
	UFUNCTION()
	void CountEnemy();
};
