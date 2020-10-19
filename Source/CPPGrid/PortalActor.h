// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "PortalActor.generated.h"

UCLASS()
class CPPGRID_API APortalActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* BlockMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* PortalMesh;

	FTimerHandle PortalAnimationTrigger;
	
public:	
	// Sets default values for this actor's properties
	APortalActor();

	UFUNCTION()
	void TimelineProgress(float Value);

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	int32 TargetIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float ZOffset;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float RepeatTimer;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;

	UFUNCTION()
	void FireAnimation();

	UFUNCTION()
	void ReturnToStartLocation();

	UFUNCTION()
	void OnPortalOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
