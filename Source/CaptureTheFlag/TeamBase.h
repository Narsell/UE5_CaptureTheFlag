// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeamBase.generated.h"

#define ECC_Base ECollisionChannel::ECC_GameTraceChannel2

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ATeamBase : public ATriggerBox
{
	GENERATED_BODY()

public:

	ATeamBase();

protected:

	void BeginPlay() override;

private:

	UFUNCTION()
	void OnFlagEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
