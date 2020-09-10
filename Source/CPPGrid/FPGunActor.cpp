// Fill out your copyright notice in the Description page of Project Settings.


#include "FPGunActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"

// Sets default values
AFPGunActor::AFPGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	RootComponent = FP_Gun;

	
}

// Called when the game starts or when spawned
void AFPGunActor::BeginPlay()
{
	Super::BeginPlay();
	if (FirePerSecond)
	{
		FireRate = 1.f / FirePerSecond;
	}
	else
	{
		FireRate = 1.f;
	}
}

// Called every frame
void AFPGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPGunActor::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, __FUNCTION__);
	//Spawn Projectile
	if (SpawnInfoProjectile)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		//Rotator and SpawnLocation need to be defined by camera instead of MuzzleSocket...
		FRotator Rotator = FP_Gun->GetSocketRotation("Muzzle");
		FVector SpawnLocation = FP_Gun->GetSocketLocation("Muzzle") + (Rotator.Vector() * 10.0f);

		AProjectileActor* Projectile = GetWorld()->SpawnActor<AProjectileActor>(SpawnInfoProjectile, SpawnLocation, Rotator, SpawnParams);
		if (Projectile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, "Got here");

			FVector LaunchDirection = Rotator.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
		
	}
}

void AFPGunActor::ActivateTrigger()
{
	Fire();
	
	GetWorld()->GetTimerManager().SetTimer(AutofireTimerHandle, this, &AFPGunActor::Fire, FireRate, true);
}

void AFPGunActor::DeactivateTrigger()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(AutofireTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(AutofireTimerHandle);
	}
}

