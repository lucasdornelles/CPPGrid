// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "DamageableActorInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereCollider->InitSphereRadius(18.0f);
	RootComponent = SphereCollider;
	SphereCollider->SetNotifyRigidBodyCollision(true);
	
	DamagePoints = 10;// Default DamagePoints value

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetCollisionProfileName("NoCollision");
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereCollider);
	ProjectileMovementComponent->InitialSpeed = 5000.0f;
	ProjectileMovementComponent->MaxSpeed = 5000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;


}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(2.0f);

	// SphereCollider OnComponentHit set here com compatibility with previously created blueprints
	SphereCollider->OnComponentHit.AddDynamic(this, &AProjectileActor::OnCompHit);

	
	
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::FireInDirection(const FVector& ShootDirection)
{
	// ProjectileMovementComponent only works on Stand Alone game
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	
}

void AProjectileActor::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Is Actor damageable?
	if (OtherActor->Implements<UDamageableActorInterface>())
	{
		// Execute damage
		Cast<IDamageableActorInterface>(OtherActor)->ResolveDamage(DamagePoints);
		if (ParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("HIT"));
	Destroy();
	
}
