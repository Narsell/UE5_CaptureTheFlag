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
	ACaptureTheFlagCharacter* GetCarrier() const { return Carrier; };

protected:

	void BeginPlay() override;

private:

	UFUNCTION()
	void OnGrabbed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	/** Pointer to flag carrier player. */
	ACaptureTheFlagCharacter* Carrier;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* PoleMesh;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* FlagMesh;

	
};
