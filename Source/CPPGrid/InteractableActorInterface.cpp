// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActorInterface.h"

// Add default functionality here for any IInteractableActorInterface functions that are not pure virtual.

EInteractableType IInteractableActorInterface::Interact()
{
	return EInteractableType::NONE;
}