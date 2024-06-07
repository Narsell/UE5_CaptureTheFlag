// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFPlayerState.h"

void ACTFPlayerState::ReceiveDamage(const float Amount)
{
	if (Amount <= 0.f) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
	OnCurrentHealthUpdateDelegate.ExecuteIfBound(CurrentHealth);
}

void ACTFPlayerState::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

}
