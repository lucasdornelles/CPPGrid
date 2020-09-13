// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));

	RootComponent = SceneRoot;

	HealthPoints = 100.0f;// Default HealthPoints value

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->SetupAttachment(SceneRoot);



}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CurveFloat)
	{

		//Initialize random ZOffset and PlayRate to give enemy a little variability
		float ZOffset = FMath::FRandRange(20.0f, 30.0f);
		float PlayRate = FMath::FRandRange(1.0f, 1.5f);


		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(true);
		CurveTimeline.SetPlayRate(PlayRate);

		StartLocation = EndLocation = GetActorLocation();
		EndLocation.Z += ZOffset;

		CurveTimeline.PlayFromStart();
	}
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}

void AEnemyActor::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	SetActorLocation(NewLocation);
}

// Receive Damage
void AEnemyActor::ResolveDamage(float Damage)
{
	// Lower Health
	HealthPoints -= Damage;
	// Destroy is less than zero
	if (HealthPoints <= 0.0f)
	{
		Destroy();
	}
}