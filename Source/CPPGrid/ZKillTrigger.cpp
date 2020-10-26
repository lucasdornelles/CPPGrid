// Fill out your copyright notice in the Description page of Project Settings.


#include "ZKillTrigger.h"
#include "DrawDebugHelpers.h"
#include "DamageableActorInterface.h"

AZKillTrigger::AZKillTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &AZKillTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AZKillTrigger::OnOverlapEnd);
}

void AZKillTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void AZKillTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{

		if (OtherActor->Implements<UDamageableActorInterface>())
		{
			// Execute damage
			Cast<IDamageableActorInterface>(OtherActor)->ResolveDamage(10000);
		}
	}
}

void AZKillTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	return;
}
