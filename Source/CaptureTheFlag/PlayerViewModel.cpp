// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerViewModel.h"
#include "CaptureTheFlagCharacter.h"
#include "CTFPlayerState.h"

void UPlayerViewModel::Initialize(ACaptureTheFlagCharacter* InPlayerCharacter, ACTFPlayerState* InPlayerState)
{
	PlayerCharacter = InPlayerCharacter;
	PlayerState = InPlayerState;

	if (PlayerCharacter)
	{
		SetMaxStamina(PlayerCharacter->GetMaxStamina());
		SetCurrentStamina(PlayerCharacter->GetCurrentStamina());
	}
	if(PlayerState)
	{
		SetMaxHealth(PlayerState->GetMaxHealth());
		SetCurrentHealth(PlayerState->GetCurrentHealth());
	}
}

float UPlayerViewModel::GetHealthPercent() const
{
	if (MaxHealth == 0.f) return 0.f;

	return CurrentHealth / MaxHealth;
}

float UPlayerViewModel::GetStaminaPercent() const
{
	if (MaxStamina == 0.f) return 0;

	return CurrentStamina / MaxStamina;
}

void UPlayerViewModel::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);

}

void UPlayerViewModel::SetCurrentHealth(float NewCurrentHealth)
{
	CurrentHealth = NewCurrentHealth;
	
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCurrentHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);

}

void UPlayerViewModel::SetMaxStamina(float NewMaxStamina)
{
	MaxStamina = NewMaxStamina;

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxStamina);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	
}

void UPlayerViewModel::SetCurrentStamina(float NewCurrentStamina)
{
	CurrentStamina = NewCurrentStamina;

	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCurrentStamina);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);

}

