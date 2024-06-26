// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (StartingHealth > MaxHealth)
	{
		StartingHealth = MaxHealth;
	}
	CurrentHealth = StartingHealth;

	GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UHealthComponent::RegenerateHealth, HealthRegenUpdateRate, true, 0.f);
}

void UHealthComponent::TakeDamage(float Amount)
{
	if (Amount > 0.f)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
		HealthUpdateDelegate.Broadcast(CurrentHealth);
		GetWorld()->GetTimerManager().SetTimer(NoDamageTimerHandle, this, &UHealthComponent::ResetHealthRegeneration, TimeToStartRegenerating, false);
	}
}

void UHealthComponent::RegenerateHealth()
{
	if (IsDead() || CurrentHealth >= MaxHealth)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + RegenerationRate, 0.f, MaxHealth);
	HealthUpdateDelegate.Broadcast(CurrentHealth);
}

void UHealthComponent::ResetHealthRegeneration()
{
	GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UHealthComponent::RegenerateHealth, HealthRegenUpdateRate, true, 0.f);
}

