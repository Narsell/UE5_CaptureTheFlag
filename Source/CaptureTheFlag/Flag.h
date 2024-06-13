// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CTFGameState.h"
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

	UFUNCTION(BlueprintCallable, Category=Getter)
	ACaptureTheFlagCharacter* GetCarrier() const;

	void SetCarrier(ACaptureTheFlagCharacter* InCarrier);

	/** Resets the carrier reference and starts the destruction timer. */
	void OnDropped();

protected:

	void BeginPlay() override;

	/** Blueprint event to set the appropriate materials/visuals of the actor to match the team */
	UFUNCTION(BlueprintImplementableEvent, Category=Setup)
	void SetTeamColorsEvent(ETeamId InTeamId);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* PoleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* FlagMesh;

private:

	/** Intermediate function which calls Destroy method. Meant to be called by destruction timer. */
	void GetDestroyed();

	/**
	 * Prepares the refences required to call the Blueprint Event 'SetTeamColorsEvent'
	 * Call on or after BeginPlay for it to work.
	 */
	void SetTeamColors();

private:

	/** Pointer to flag carrier player. */
	TWeakObjectPtr<ACaptureTheFlagCharacter> Carrier = nullptr;

	/** Time before being destroyed after being dropped. */
	UPROPERTY(EditAnywhere, Category=Setup)
	float TimeBeforeDestruction = 3.f;

	/** Team this flag belongs to */
	ETeamId TeamId = ETeamId::NONE;

	FTimerHandle DestructionTimer;

};
