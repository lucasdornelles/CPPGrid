// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageableActorInterface.h"
#include "Components/TimelineComponent.h"
#include "EnemyActor.generated.h"

UCLASS()
class CPPGRID_API AEnemyActor : public AActor, public IDamageableActorInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* EnemyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* SceneRoot;

	// PlayerPerception Capsule
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UCapsuleComponent* VisionCapsule;

	// Set HealthPoints on Blueprint instance
	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAcess = "true"))
	int32 HealthPoints;

	// Arrow Component for firing projectile
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UArrowComponent* ArrowComponent;

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
	AEnemyActor();

	//Floating motion timeline function
	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	//Curve to control floating movement
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Pure c++ interface function
	virtual void ResolveDamage(int32 Damage) override;

	void Fire();

	void ResetEnemy();

	class ACharacter* PlayerCharacterRef;

private:
	bool IsPlayerVisible;

	// Overlap Event
	UFUNCTION()
	void VisionCapsuleOverlap(UPrimitiveComponent * OverlapComponent,
		AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	bool IsFiring;

	// Spawn Rotator and vector to reset enemy
	// Those will be discarded when respawn enemys is implemented
	FRotator BeginPlayRotator;

};
