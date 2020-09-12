// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.h"
#include "Camera/CameraComponent.h"
#include "FPGunActor.generated.h"

UCLASS()
class CPPGRID_API AFPGunActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	// Timer for auto fire
	FTimerHandle AutofireTimerHandle;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAcess = "true"))
	float FirePerSecond;

	float FireRate;

	// BP class of Projectile to be spawned
	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class AProjectileActor> SpawnInfoProjectile;
	
	
public:	
	// Sets default values for this actor's properties
	AFPGunActor();

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FVector MuzzleOffset;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Spawn projectile
	void Fire();

	// Set timeline for auto fire
	void ActivateTrigger();

	// Clear timeline for auto fire
	void DeactivateTrigger();

	class UCameraComponent* CameraReference;

	// Get CameraReference instead of player to prevent circular dependency
	void SetCameraReference(UCameraComponent* InCamera);

};
