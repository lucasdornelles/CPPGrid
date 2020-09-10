// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAnimInstance.h"

#include "HeroCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/PlayerController.h"

UHeroAnimInstance::UHeroAnimInstance()
{
	IsInAir = false;
	Speed = 0.f;
	IsFiring = false;
}

// AnimInstance "BeginPlay"
void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// cache pawn for later use
	Owner = TryGetPawnOwner();
}

// AnimInstance Tick
void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ensure that owner is valid
	if (!Owner)
	{
		return;
	}

	if (Owner->IsA(AHeroCharacter::StaticClass()))
	{
		AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(Owner);
		if (HeroCharacter)
		{
			IsInAir = HeroCharacter->GetMovementComponent()->IsFalling();
			Speed = HeroCharacter->GetVelocity().Size();
			IsFiring = HeroCharacter->IsFiring;
		}
	}
}