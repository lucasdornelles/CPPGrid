// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.h"
#include "FPGunActor.generated.h"

UCLASS()
class CPPGRID_API AFPGunActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	FTimerHandle AutofireTimerHandle;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAcess = "true"))
	float FirePerSecond;

	float FireRate;

	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class AProjectileActor> SpawnInfoProjectile;

	
	
public:	
	// Sets default values for this actor's properties
	AFPGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

	void ActivateTrigger();

	void DeactivateTrigger();

};
