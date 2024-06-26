// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PlayerViewModel.generated.h"

class ACaptureTheFlagCharacter;
class ACTFPlayerState;
class UStaminaComponent;

/**
 *
 */
UCLASS()
class CAPTURETHEFLAG_API UPlayerViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/** Sets the initial state on the view based on the initial model state */
	void Initialize(ACaptureTheFlagCharacter* InPlayerCharacter, ACTFPlayerState* InPlayerState);

	/** Getters */
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetMaxHealth() const { return FText::AsNumber(MaxHealth); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetCurrentHealth() const { return FText::AsNumber(CurrentHealth); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetMaxStamina() const { return FText::AsNumber(MaxStamina); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetCurrentStamina() const { return FText::AsNumber(CurrentStamina); }

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetStaminaPercent() const;

	/** Setters */

	void SetMaxHealth(float NewMaxHealth);

	void SetCurrentHealth(float NewCurrentHealth);

private:

	void SetMaxStamina(float NewMaxStamina);

	void SetCurrentStamina(float Stamina);

private:

	float MaxHealth;
	float CurrentHealth;
	float MaxStamina;
	float CurrentStamina;

	ACaptureTheFlagCharacter* PlayerCharacter = nullptr;
	UStaminaComponent* PlayerStaminaComp = nullptr;
	ACTFPlayerState* PlayerState = nullptr;

};
