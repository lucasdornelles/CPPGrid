// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuGameMode.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API AMainMenuGameMode : public AMenuGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void ChangeLevel() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* SoundBase;
};
