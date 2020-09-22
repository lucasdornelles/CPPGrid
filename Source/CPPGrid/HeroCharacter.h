// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPGunActor.h"
#include "DamageableActorInterface.h"
#include "Components/TimelineComponent.h"
#include "HeroCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

UCLASS()
class CPPGRID_API AHeroCharacter : public ACharacter, public IDamageableActorInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UCapsuleComponent* CharacterHitbox;
	
	UPROPERTY(EditAnywhere, Category = Weapon, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class AFPGunActor> SpawnInfoFP_Gun;

	//Sticked a UPROPERTY() just to be sure it is not garbage collected

	UPROPERTY()
	class AFPGunActor* FP_Gun;

	// Set HealthPoints on Blueprint instance
	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAcess = "true"))
	int32 HealthPoints;

	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAcess = "true"))
	int32 RestoredHP;

	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAcess = "true"))
	float RestoreSpeed;

	

	// Timer for restore health
	FTimerHandle RestoreHealthTimerHandle;

	

public:
	// Sets default values for this character's properties
	AHeroCharacter();

	int32 CurrentHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FOnPlayerDeath PlayerDeath;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float BaseWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float BaseSprintSpeed;

	bool IsFiring;

	void RestoreHealth();

	// Pure c++ interface function
	virtual void ResolveDamage(int32 Damage) override;

protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/**
	* Called via input to start sprint movement
	*/
	void StartSprint();

	/**
	* Called via input to stop sprint movement
	*/
	void StopSprint();

	/**
	* Called via input to fire weapon
	*/
	void StartFire();

	void EndFire();

private:

	bool IsRestoringHealth;

	void UpdateUIHealth(int32 NewValue);

	void InitializeUITotalHealth(int32 Value);

	bool IsSprinting;

};
