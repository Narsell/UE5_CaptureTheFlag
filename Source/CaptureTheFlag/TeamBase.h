// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "Flag.h"
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeamBase.generated.h"

#define ECC_Base ECollisionChannel::ECC_GameTraceChannel2

class ACTFGameMode;
class APlayerSpawnZone;
class ASpawnZone;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API ATeamBase : public ATriggerBox
{
	GENERATED_BODY()

public:

	ATeamBase();

	/** Returns the team ID that this base belongs to */
	UFUNCTION(BlueprintCallable, Category = Team)
	ETeamId GetTeamId() const { return TeamId; };

	/** Gets the array of spawn zones binded to this base */
	const TArray<ASpawnZone*>& GetSpawnZones() const { return SpawnZones; }

protected:

	void BeginPlay() override;

	/**
	* Updates the spawn zones data to point back to this base.
	* Also validates and removes duplicates across other team bases.
	*/
	UFUNCTION(BlueprintCallable)
	void SetupSpawnZones();

private:

	UFUNCTION()
	void OnFlagEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditInstanceOnly, Category=Setup)
	TArray<ASpawnZone*> SpawnZones;

	/**  Team identifier. */
	UPROPERTY(EditInstanceOnly, Category=Setup, BlueprintReadOnly, meta=(AllowPrivateAccess))
	ETeamId TeamId = ETeamId::A;

	/** Scene component to mark the location the flag will be dropped in momentarily. */
	UPROPERTY(EditDefaultsOnly, Category=Flag)
	USceneComponent* DropFlagSocket;

	ACTFGameMode* GameMode = nullptr;
};
