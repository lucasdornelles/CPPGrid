// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	class AHeroCharacter* PlayerCharacter;

	void PossesCheckpoint();

	void PossesPlayerCharacter();

	void StopEnemyFire();

public:

	UFUNCTION()
	void PlayerCharacterDeath();

	UFUNCTION()
	void RestartGame();
	
};
