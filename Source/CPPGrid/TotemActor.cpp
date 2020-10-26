// Fill out your copyright notice in the Description page of Project Settings.


#include "TotemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "KeyActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ATotemActor::ATotemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));

	RootComponent = SceneRoot;

	TotemBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TotemBaseMesh"));
	RingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingMesh"));
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));

	TotemBaseMesh->SetupAttachment(RootComponent);
	RingMesh->SetupAttachment(RootComponent);
	HitBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATotemActor::BeginPlay()
{
	Super::BeginPlay();

	TotemBaseMesh->SetScalarParameterValueOnMaterials("Emissive", 10.0f);
	RingMesh->SetScalarParameterValueOnMaterials("Emissive", 10.0f);

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(true);
		CurveTimeline.SetPlayRate(1.0f);

		StartLocation = EndLocation = RingMesh->GetComponentLocation();
		StartLocation.Z += 10.0f;
		EndLocation.Z += ZOffset;
	}
	
}

// Called every frame
void ATotemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);

}

void ATotemActor::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	RingMesh->SetWorldLocation(NewLocation);
	
}

EInteractableType ATotemActor::Interact()
{
	return InteractableType;
}

void ATotemActor::ActivateTotem()
{

	if (SpawnInfoKeyActor)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator Rotator;
		FVector SpawnLocation = this->RootComponent->GetComponentLocation();
		SpawnLocation.Z += 150.0f;
		UWorld* World = GetWorld();
		if (World)
			World->SpawnActor<AKeyActor>(SpawnInfoKeyActor, SpawnLocation, Rotator, SpawnParams);
	}

	TotemBaseMesh->SetScalarParameterValueOnMaterials("Emissive", 50.0f);
	RingMesh->SetScalarParameterValueOnMaterials("Emissive", 50.0f);
	CurveTimeline.PlayFromStart();
}

