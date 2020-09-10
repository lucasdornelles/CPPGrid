// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsFiring;

public:
	UHeroAnimInstance();

	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	APawn* Owner;
};
