// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PlayerViewModel.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UPlayerViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/** Getters */

	float GetMaxHealth() const;

	float GetCurrentHealth() const;

	float GetMaxStamina() const;

	float GetCurrentStamina() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetStaminaPercent() const;

	/** Setters */

	void SetMaxHealth(float NewMaxHealth);

	void SetCurrentHealth(float NewCurrentHealth);

	void SetMaxStamina(float NewMaxStamina);

	void SetCurrentStamina(float NewCurrentStamina);

protected:

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	float MaxStamina;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	float CurrentStamina;

	
};
