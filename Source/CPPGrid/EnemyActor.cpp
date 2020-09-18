// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"
#include "ProjectileActor.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));

	RootComponent = SceneRoot;

	HealthPoints = 100.0f;// Default HealthPoints value

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->SetupAttachment(RootComponent);

	VisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("VisionCapsule"));
	VisionCapsule->SetupAttachment(RootComponent);
	VisionCapsule->InitCapsuleSize(400.0f, 800.0f);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

	IsFiring = false;

}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	IsPlayerVisible = false;
	Super::BeginPlay();
	BeginPlayRotator = GetActorRotation();

	// Attach overlap event to OnComponentOverlap
	VisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::VisionCapsuleOverlap);
	
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

	if (FirePerSecond)
	{
		FireRate = 1.f / FirePerSecond;
	}
	else
	{
		FireRate = 1.f;
	}

	// Try to get player character
	ACharacter*  PlayerPointer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerPointer)
	{
		// If it succeds set player character reference, no need to cast
		PlayerCharacterRef = PlayerPointer;
	}

}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);

	if (IsPlayerVisible)
	{
		// If player is visible look at player
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
			PlayerCharacterRef->GetActorLocation()));

		if (!IsFiring)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				World->GetTimerManager().SetTimer(AutofireTimerHandle, this, &AEnemyActor::Fire, FireRate, true);

			}
			IsFiring = true;
		}
	}
}

void AEnemyActor::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	SetActorLocation(NewLocation);
}

// Receive Damage
void AEnemyActor::ResolveDamage(float Damage)
{
	if (!IsPlayerVisible)
	{
		// If hit player character is visible
		IsPlayerVisible = true;
	}

	// Lower Health
	HealthPoints -= Damage;
	// Destroy is less than zero
	if (HealthPoints <= 0.0f)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			if (World->GetTimerManager().IsTimerActive(AutofireTimerHandle))
			{
				World->GetTimerManager().ClearTimer(AutofireTimerHandle);
			}
			Destroy();
		}
	}
}

void AEnemyActor::VisionCapsuleOverlap(UPrimitiveComponent * OverlapComponent,
	AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == PlayerCharacterRef)
	{
		// if overlaping actor is player character player character is visible
		IsPlayerVisible = true;
	}
}

void AEnemyActor::Fire()
{
	if (SpawnInfoProjectile)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		FVector SpawnLocation = ArrowComponent->GetComponentLocation();
		FRotator SpawnRotator = ArrowComponent->GetComponentRotation();
		FVector LaunchDirection = SpawnRotator.Vector();

		UWorld* World = GetWorld();
		if (World)
		{

			AProjectileActor* Projectile = World->SpawnActor<AProjectileActor>(SpawnInfoProjectile, SpawnLocation, SpawnRotator, SpawnParams);

			if (Projectile)
			{
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AEnemyActor::ResetEnemy()
{
	if (IsPlayerVisible)
	{
		IsPlayerVisible = false;
	}

	if (IsFiring)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			if (World->GetTimerManager().IsTimerActive(AutofireTimerHandle))
			{
				World->GetTimerManager().ClearTimer(AutofireTimerHandle);
				IsFiring = false;
			}
		}
	}
	
	SetActorRotation(BeginPlayRotator);
}
