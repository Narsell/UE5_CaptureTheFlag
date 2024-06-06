// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "Flag.h"
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeamBase.generated.h"

#define ECC_Base ECollisionChannel::ECC_GameTraceChannel2

class ACTFGameMode;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API ATeamBase : public ATriggerBox
{
	GENERATED_BODY()

public:

	ATeamBase();

	UFUNCTION(BlueprintCallable, Category=Team)
	const ETeamId& GetTeamId() const { return TeamId; };

protected:

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetupSpawnPoints();

private:

	UFUNCTION()
	void OnFlagEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	/** Scene component to mark the location the flag will be dropped in momentarily. */
	UPROPERTY(EditDefaultsOnly, Category=Flag)
	USceneComponent* FlagSocket;

	/**  Team identifier. */
	UPROPERTY(EditInstanceOnly, Category=Setup)
	ETeamId TeamId;

	/**  Number of flags to spawn for the team belonging to this base. */
	UPROPERTY(EditInstanceOnly, Category=Setup)
	int32 NumberOfFlags = 2;

	/** Class of the Flag instance. */
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AFlag> FlagType;

	ACTFGameMode* GameMode;

};
