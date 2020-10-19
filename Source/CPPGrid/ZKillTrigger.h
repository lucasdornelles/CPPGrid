// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "ZKillTrigger.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API AZKillTrigger : public ATriggerVolume
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

public:

	AZKillTrigger();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
	
};
