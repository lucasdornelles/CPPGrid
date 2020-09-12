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
	// If BP class to spawn was defined Spawn Projectile
	if (SpawnInfoProjectile)
	{
		//Prepare Spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		//Use GetInstigator for foward compatibility
		SpawnParams.Instigator = GetInstigator();

		//If cast was sucefull
		if (CameraReference)
		{
			//Get camera Location from player character
			FVector CameraLocation = CameraReference->GetComponentLocation();
			//Get camera Rotation from player character
			FRotator CameraRotation = CameraReference->GetComponentRotation();
			
			//Determine Spawn location using offset
			FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
			FRotator MuzzleRotation = CameraRotation;

			//Spawn projectile
			AProjectileActor* Projectile = GetWorld()->SpawnActor<AProjectileActor>(SpawnInfoProjectile, MuzzleLocation, MuzzleRotation, SpawnParams);
			
			//If Spawn was sucefull we should have a pointer to the projectile
			if (Projectile)
			{
				//Set the direction for the projectile velocity
				FVector LaunchDirection = MuzzleRotation.Vector();
				//Fire Projectile
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AFPGunActor::ActivateTrigger()
{
	// Fire Once
	Fire();
	
	// And Set timer for auto fire
	GetWorld()->GetTimerManager().SetTimer(AutofireTimerHandle, this, &AFPGunActor::Fire, FireRate, true);
}

void AFPGunActor::DeactivateTrigger()
{
	// If timer is active, clear it
	if (GetWorld()->GetTimerManager().IsTimerActive(AutofireTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(AutofireTimerHandle);
	}
	// If timer is not active but not clear it will be substituted by a new one when the timer is set
	// So we only need to check if it is active
}

void AFPGunActor::SetCameraReference(UCameraComponent* InCamera)
{
	CameraReference = InCamera;
}
