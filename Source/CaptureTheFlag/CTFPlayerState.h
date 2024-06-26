// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CTFPlayerState.generated.h"

class UPlayerViewModel;
class UHealthComponent;

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsFlagCarrier() const { return bIsFlagCarrier; }

	void SetIsFlagCarrier(const bool IsFlagCarrier) { bIsFlagCarrier = IsFlagCarrier; }

protected:

	virtual void BeginPlay() override;

protected:

	UHealthComponent* PlayerHealthComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Player)
	bool bIsFlagCarrier = false;

};
