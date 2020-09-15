// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "DamageableActorInterface.h"
#include "EnemyActor.generated.h"

UCLASS()
class CPPGRID_API AEnemyActor : public AActor, public IDamageableActorInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* EnemyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USphereComponent* SceneRoot;

	// PlayerPerception Capsule
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UCapsuleComponent* VisionCapsule;

	// Set HealthPoints on Blueprint instance
	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAcess = "true"))
	float HealthPoints;
	
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
	virtual void ResolveDamage(float Damage) override;

	class ACharacter* PlayerCharacterRef;

private:
	bool IsPlayerVisible;

	// Overlap Event
	UFUNCTION()
	void VisionCapsuleOverlap(UPrimitiveComponent * OverlapComponent,
		AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
