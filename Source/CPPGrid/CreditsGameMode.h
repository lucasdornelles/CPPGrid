// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MenuGameMode.h"
#include "CreditsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API ACreditsGameMode : public AMenuGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void ChangeLevel() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* SoundBase;
};
