// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerViewModel.h"

float UPlayerViewModel::GetMaxHealth() const
{
	return MaxHealth;
}

float UPlayerViewModel::GetCurrentHealth() const
{
	return MaxHealth;
}

float UPlayerViewModel::GetHealthPercent() const
{
	if (MaxHealth == 0.f) return 0.f;

	return CurrentHealth / MaxHealth;
}

float UPlayerViewModel::GetMaxStamina() const
{
	return MaxStamina;
}

float UPlayerViewModel::GetCurrentStamina() const
{
	return CurrentStamina;
}

float UPlayerViewModel::GetStaminaPercent() const
{
	if (MaxStamina == 0.f) return 0.f;

	return CurrentStamina / MaxStamina;
}

void UPlayerViewModel::SetMaxHealth(float NewMaxHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewMaxHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UPlayerViewModel::SetCurrentHealth(float NewCurrentHealth)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, NewCurrentHealth))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UPlayerViewModel::SetMaxStamina(float NewMaxStamina)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxStamina, NewMaxStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}
}

void UPlayerViewModel::SetCurrentStamina(float NewCurrentStamina)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentStamina, NewCurrentStamina))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}
}

