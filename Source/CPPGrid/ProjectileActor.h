// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileActor.generated.h"

UCLASS()
class CPPGRID_API AProjectileActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* ProjectileMesh;

	// Set DamagePoints on Blueprint instance
	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAcess = "true"))
	int32 DamagePoints;

	UPROPERTY(EditAnywhere, Category = Particle, meta = (AllowPrivateAcess = "true"))
	UParticleSystem* ParticleSystem;
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	USphereComponent* SphereCollider;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float FireVolume;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	float HitVolume;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundAttenuation* AttenuationSettings;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* SoundFire;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* SoundHit;

};
