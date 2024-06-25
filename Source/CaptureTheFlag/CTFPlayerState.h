// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CTFPlayerState.generated.h"

DECLARE_DELEGATE_OneParam(FOnHealthUpdateSignature, float NewHealth);

class UPlayerViewModel;

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	void ReceiveDamage(const float Amount);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return MaxHealth; };

	UFUNCTION(BlueprintCallable)
	bool IsFlagCarrier() const { return bIsFlagCarrier; }

	void SetIsFlagCarrier(const bool IsFlagCarrier) { bIsFlagCarrier = IsFlagCarrier; }

	void SetPlayerViewModel(UPlayerViewModel* InPlayerViewModel);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Player)
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Player)
	float CurrentHealth = MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Player)
	bool bIsFlagCarrier = false;

private:

	UPlayerViewModel* PlayerViewModel = nullptr;
	
};
