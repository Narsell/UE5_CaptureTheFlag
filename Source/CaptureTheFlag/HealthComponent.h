// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthUpdateSignature, float Health)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPTURETHEFLAG_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

	FOnHealthUpdateSignature HealthUpdateDelegate;

	float GetCurrentHealth() const { return CurrentHealth; }

	float GetMaxHealth() const { return MaxHealth; }

	bool IsDead() const { return CurrentHealth <= 0.f; }

	void TakeDamage(float Amount);

protected:

	virtual void BeginPlay() override;

private:

	void RegenerateHealth();

	void ResetHealthRegeneration();

private:

	UPROPERTY(EditAnywhere, Category = Health, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = Health, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float StartingHealth = MaxHealth;

	UPROPERTY(EditAnywhere, Category = Health, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float CurrentHealth = StartingHealth;

	UPROPERTY(EditAnywhere, Category = Health, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RegenerationRate = 5.f;

	/** Time required after taking damage to start regenerating health */
	UPROPERTY(EditAnywhere, Category = Health, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TimeToStartRegenerating = 5.f;

	float HealthRegenUpdateRate = 0.1f;

	FTimerHandle RegenTimerHandle;

	FTimerHandle NoDamageTimerHandle;

};
