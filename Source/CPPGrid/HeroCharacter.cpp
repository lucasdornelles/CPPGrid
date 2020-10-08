// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameplayHUD.h"
#include "Engine.h"
//Engine is temporary

// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	BaseWalkSpeed = 700.f;
	BaseSprintSpeed = 1000.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamer"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-30.f, 0.f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -15.0f, 7.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	CharacterHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CharacterHitbox"));
	CharacterHitbox->SetupAttachment(RootComponent);
	CharacterHitbox->InitCapsuleSize(55.f, 96.0f);
	CharacterHitbox->SetCollisionProfileName("CharacterHitbox");

	HealthPoints = 100;// Default HealthPoints value

	RestoredHP = 10;// Default HP restore
	RestoreSpeed = 0.5f;// Default restore Speed

	TraceDistance = 300.0f;

	TraceRadius = 100.0f;
	
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	//Spawn FP_Gun Actor
	if (SpawnInfoFP_Gun)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FRotator Rotator;
		FVector SpawnLocation = this->RootComponent->GetComponentLocation();
		FP_Gun = GetWorld()->SpawnActor<AFPGunActor>(SpawnInfoFP_Gun, SpawnLocation, Rotator, SpawnParams);
		//Attach gun Actor to Skeleton
		FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

		FP_Gun->SetCameraReference(FirstPersonCameraComponent);
	}

	CurrentHealth = HealthPoints;
	InitializeUITotalHealth(CurrentHealth);

	// initialize booleans
	IsFiring = false;
	IsSprinting = false;
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind Jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHeroCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHeroCharacter::StopJumping);

	// Bind Movement events
	PlayerInputComponent->BindAxis("MoveFoward", this, &AHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);

	// Bind Sprint events
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHeroCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHeroCharacter::StopSprint);

	// Bind Fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHeroCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AHeroCharacter::EndFire);

	// Bind Camera movement
	// Mouse Input
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// Gamepad input
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHeroCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHeroCharacter::TurnAtRate);

	// Bind Interact event
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHeroCharacter::Interact);


}

void AHeroCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHeroCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AHeroCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHeroCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHeroCharacter::StartFire()
{
	if (!IsFiring)
	{
		IsFiring = true;
		FP_Gun->ActivateTrigger();
	}
}

void AHeroCharacter::EndFire()
{
	if (IsFiring)
	{
		IsFiring = false;
		FP_Gun->DeactivateTrigger();
	}
}

void AHeroCharacter::StartSprint()
{
	if (!IsSprinting)
	{
		IsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = BaseSprintSpeed;
	}
}

void AHeroCharacter::StopSprint()
{
	if (IsSprinting)
	{
		IsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	}
}

void AHeroCharacter::ResolveDamage(int32 Damage)
{
	// Only resolve damage if health is higher than zero to prevend broadcasting death multiple times
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage;
		UpdateUIHealth(CurrentHealth);

		if (!IsRestoringHealth)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				World->GetTimerManager().SetTimer(RestoreHealthTimerHandle,
					this, &AHeroCharacter::RestoreHealth, RestoreSpeed, true);
				IsRestoringHealth = true;//set here to not reinitialize timer if damage is dealt faster than restorespeed
			}
		}
		if (CurrentHealth <= 0)
		{
			CurrentHealth = 0;
			UWorld* World = GetWorld();
			if (World)
			{
				if (World->GetTimerManager().IsTimerActive(RestoreHealthTimerHandle))
				{
					World->GetTimerManager().ClearTimer(RestoreHealthTimerHandle);
					IsRestoringHealth = false;
				}
			}

			if (IsFiring)
			{
				EndFire();
			}

			if (IsSprinting)
			{
				StopSprint();
			}
			UpdateUIHealth(CurrentHealth);
			PlayerDeath.Broadcast();

		}
	}
}

void AHeroCharacter::ResetCharacter()
{
	CurrentHealth = HealthPoints;
	UpdateUIHealth(CurrentHealth);
}

void AHeroCharacter::RestoreHealth()
{
	IsRestoringHealth = true;
	CurrentHealth += RestoredHP;
	

	if (CurrentHealth >= HealthPoints)
	{
		CurrentHealth = HealthPoints;
		
		UWorld* World = GetWorld();
		if (World)
		{
			if (World->GetTimerManager().IsTimerActive(RestoreHealthTimerHandle))
			{
				World->GetTimerManager().ClearTimer(RestoreHealthTimerHandle);
				IsRestoringHealth = false;
			}
		}
	}
	UpdateUIHealth(CurrentHealth);
}

void AHeroCharacter::UpdateUIHealth(int32 NewValue)
{
	AGameplayHUD* GameplayHUD = Cast<AGameplayHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (GameplayHUD)
	{
		GameplayHUD->UpdateHealthText(NewValue);
	}
}

void AHeroCharacter::InitializeUITotalHealth(int32 Value)
{
	AGameplayHUD* GameplayHUD = Cast<AGameplayHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (GameplayHUD)
	{
		GameplayHUD->InitializeTotalHealth(Value);
	}
}

void AHeroCharacter::Interact()
{
	// Interact whit actors implementing InteractableActorInterface
	UWorld* World = GetWorld();
	if (World)
	{
		FVector Start = FirstPersonCameraComponent->GetComponentLocation();
		FRotator Rotation = FirstPersonCameraComponent->GetComponentRotation();
		FVector End = Start + (Rotation.Vector() * TraceDistance);

		FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, this);

		FHitResult InteractHit = FHitResult(ForceInit);

		bool bIsHit = World->SweepSingleByChannel(InteractHit, Start, End, Rotation.Quaternion(),
			ECC_GameTraceChannel5, FCollisionShape::MakeSphere(18.0f), TraceParams);
		if (bIsHit && InteractHit.GetActor()->Implements<UInteractableActorInterface>())
		{
			EInteractableType InteractType = Cast<IInteractableActorInterface>(InteractHit.GetActor())->Interact();
			OnInteract.Broadcast(InteractType);
		}
	}
}