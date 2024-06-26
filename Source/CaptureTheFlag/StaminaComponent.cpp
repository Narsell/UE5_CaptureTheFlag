// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"

UStaminaComponent::UStaminaComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UStaminaComponent::SetIsSprinting(const bool IsSprinting)
{
	bIsSprinting = IsSprinting;
}


void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	if (StartingStamina > MaxStamina)
	{
		StartingStamina = MaxStamina;
	}
	if (CurrentStamina > StartingStamina)
	{
		CurrentStamina = StartingStamina;
	}
	CurrentStamina = StartingStamina;

	GetWorld()->GetTimerManager().SetTimer(UpdateTimerHandle, this, &UStaminaComponent::UpdateStamina, StaminaUpdateRate, true);
}

void UStaminaComponent::UpdateStamina()
{
	if(bIsSprinting && !FMath::IsNearlyZero(CurrentStamina))
	{
		CurrentStamina = FMath::Clamp(CurrentStamina - UsageRate, 0.f, MaxStamina);
	}
	else if (!bIsSprinting && !FMath::IsNearlyEqual(CurrentStamina, MaxStamina))
	{
		CurrentStamina = FMath::Clamp(CurrentStamina + RegenerationRate, 0.f, MaxStamina);
	}
	else
	{
		return;
	}
	StaminaUpdateDelegate.Broadcast(CurrentStamina);
}



