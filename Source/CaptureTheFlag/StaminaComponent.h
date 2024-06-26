// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaUpdateSignature, float Stamina)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPTURETHEFLAG_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnStaminaUpdateSignature StaminaUpdateDelegate;

	UStaminaComponent();

	float GetCurrentStamina() const { return CurrentStamina; }

	float GetMaxStamina() const { return MaxStamina; }

	bool HasStaminaLeft() const { return CurrentStamina > 0.f; }

	bool IsSprinting() const { return bIsSprinting; }

	void SetIsSprinting(const bool IsSprinting);

protected:

	virtual void BeginPlay() override;

private:

	void UpdateStamina();

private:

	UPROPERTY(VisibleInstanceOnly)
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, Category=Stamina, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxStamina = 200.f;

	UPROPERTY(EditAnywhere, Category = Stamina, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float StartingStamina = MaxStamina;

	UPROPERTY(EditAnywhere, Category = Stamina, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float CurrentStamina = StartingStamina;

	UPROPERTY(EditAnywhere, Category = Stamina, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RegenerationRate = 5.f;

	UPROPERTY(EditAnywhere, Category = Stamina, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float UsageRate = 8.f;

	float StaminaUpdateRate = 0.1f;

	FTimerHandle UpdateTimerHandle;

};
