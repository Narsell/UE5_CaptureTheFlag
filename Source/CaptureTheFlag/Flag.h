// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Flag.generated.h"

#define ECC_Flag ECollisionChannel::ECC_GameTraceChannel1

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API AFlag : public ATriggerBox
{
	GENERATED_BODY()

public:

	AFlag();

	UFUNCTION(BlueprintCallable)
	ACaptureTheFlagCharacter* GetCarrier() const;

	void SetCarrier(ACaptureTheFlagCharacter* InCarrier);

	/** Resets the carrier reference and starts the destruction timer. */
	void OnDropped();

protected:

	void BeginPlay() override;

private:

	/** Intermediate function which calls Destroy method. Meant to be called by destruction timer. */
	void GetDestroyed();

private:

	/** Pointer to flag carrier player. */
	TWeakObjectPtr<ACaptureTheFlagCharacter> Carrier;

	/** Time before being destroyed after being dropped. */
	UPROPERTY(EditAnywhere, Category = Setup)
	float TimeBeforeDestruction = 3.f;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* PoleMesh;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* FlagMesh;

	FTimerHandle DestructionTimer;
	
};
