// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFPlayerState.h"
#include "PlayerViewModel.h"

void ACTFPlayerState::ReceiveDamage(const float Amount)
{
	if (Amount <= 0.f) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);

	if (PlayerViewModel)
	{
		PlayerViewModel->SetCurrentHealth(CurrentHealth);
	}
}

void ACTFPlayerState::SetPlayerViewModel(UPlayerViewModel* InPlayerViewModel)
{
	if (InPlayerViewModel)
	{
		PlayerViewModel = InPlayerViewModel;
		PlayerViewModel->SetMaxHealth(MaxHealth);
		PlayerViewModel->SetCurrentHealth(CurrentHealth);
	}
}

void ACTFPlayerState::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

}
