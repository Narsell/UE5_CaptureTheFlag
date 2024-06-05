// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Flag.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API AFlag : public ATriggerBox
{
	GENERATED_BODY()

public:

	AFlag();

protected:

	void BeginPlay() override;

private:

	UFUNCTION()
	void OnGrabbed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* PoleMesh;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* FlagMesh;
	
};
