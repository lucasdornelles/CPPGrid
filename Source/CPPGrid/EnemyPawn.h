// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "DamageableActorInterface.h"
#include "Components/TimelineComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnemyPawn.generated.h"

UCLASS()
class CPPGRID_API AEnemyPawn : public APawn, public IDamageableActorInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* EnemyMesh;

	// Set HealthPoints on Blueprint instance
	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAcess = "true"))
	int32 HealthPoints;

	// If a Movement component became necessary this can be used
	//UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	//class UFloatingPawnMovement* MovementComponent;

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Floating motion timeline function
	UFUNCTION()
	void TimelineProgress(float Value);

	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviourTree;

	// Pure c++ interface function
	virtual void ResolveDamage(int32 Damage) override;

private:
	
	// Sensing Player function
	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn);

};
