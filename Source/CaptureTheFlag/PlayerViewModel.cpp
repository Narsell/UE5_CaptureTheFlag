// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerViewModel.h"
#include "CaptureTheFlagCharacter.h"
#include "CTFPlayerState.h"
#include "StaminaComponent.h"

void UPlayerViewModel::Initialize(ACaptureTheFlagCharacter* InPlayerCharacter, ACTFPlayerState* InPlayerState)
{
	PlayerCharacter = InPlayerCharacter;
	PlayerState = InPlayerState;

	if (PlayerCharacter)
	{
		PlayerStaminaComp = PlayerCharacter->GetStaminaComponent();

		SetMaxStamina(PlayerStaminaComp->GetMaxStamina());
		SetCurrentStamina(PlayerStaminaComp->GetCurrentStamina());

		PlayerStaminaComp->StaminaUpdateDelegate.AddUObject(this, &UPlayerViewModel::SetCurrentStamina);
	}
	if(PlayerState)
	{
		SetMaxHealth(PlayerState->GetMaxHealth());
		SetCurrentHealth(PlayerState->GetCurrentHealth());
	}
}

float UPlayerViewModel::GetHealthPercent() const
{
	if (MaxHealth > 0.f)
	{
		return CurrentHealth / MaxHealth;
	}
	return 0.f;
}

float UPlayerViewModel::GetStaminaPercent() const
{
	if (MaxStamina > 0.f)
	{
		return CurrentStamina / MaxStamina;
	}
	return 0.f;
}

void UPlayerViewModel::SetMaxHealth(float NewMaxHealth)
{
	if (MaxHealth != NewMaxHealth)
	{
		MaxHealth = NewMaxHealth;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxHealth);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}

}

void UPlayerViewModel::SetCurrentHealth(float NewCurrentHealth)
{
	if (CurrentHealth != NewCurrentHealth)
	{
		CurrentHealth = NewCurrentHealth;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCurrentHealth);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}

}

void UPlayerViewModel::SetMaxStamina(float NewMaxStamina)
{
	if (MaxStamina != NewMaxStamina)
	{
		MaxStamina = NewMaxStamina;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxStamina);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}

}

void UPlayerViewModel::SetCurrentStamina(float NewCurrentStamina)
{
	if (CurrentStamina != NewCurrentStamina)
	{
		CurrentStamina = NewCurrentStamina;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCurrentStamina);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
	}
}
