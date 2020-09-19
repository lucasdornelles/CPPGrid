// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyAIController.h"



// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(20.0f);
	RootComponent = SphereComponent;

	HealthPoints = 100;// Default HealthPoints value

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->SetupAttachment(RootComponent);

	// Initialization of movemento component
	//MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	//MovementComponent->SetUpdatedComponent(RootComponent);

	//Initialize Sensing component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
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

	// If component exist add sensing player function to vision sense
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyPawn::OnPlayerCaught);
	}
	
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn::ResolveDamage(int32 Damage)
{
	// Lower Health
	HealthPoints -= Damage;
	// Destroy is less than zero
	if (HealthPoints <= 0)
	{
		Destroy();
	}
}

void AEnemyPawn::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	SetActorLocation(NewLocation);
}

void AEnemyPawn::OnPlayerCaught(APawn* Pawn)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		// If we got a player pass it to the AIcontroller
		AIController->SetPlayerCaught(Pawn);
	}
}

