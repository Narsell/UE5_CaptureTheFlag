// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "Flag.h"
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeamBase.generated.h"

#define ECC_Base ECollisionChannel::ECC_GameTraceChannel2

class ACTFGameMode;
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

	UFUNCTION(BlueprintCallable, Category=Team)
	const ETeamId& GetTeamId() const { return TeamId; };

protected:

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ResizeSpawnZones();

private:

	UFUNCTION()
	void OnFlagEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:

	UPROPERTY(EditInstanceOnly, Category=Setup)
	TArray<ASpawnZone*> FlagSpawnZones;

	UPROPERTY(EditInstanceOnly, Category=Setup)
	TArray<ASpawnZone*> PlayerSpawnZones;

	/**  Team identifier. */
	UPROPERTY(EditInstanceOnly, Category=Setup, BlueprintReadOnly, meta=(AllowPrivateAccess))
	ETeamId TeamId;

	/** Class of the Flag instance. */
	UPROPERTY(EditAnywhere, Category=Setup)
	TSubclassOf<AFlag> FlagType;

	/** Scene component to mark the location the flag will be dropped in momentarily. */
	UPROPERTY(EditDefaultsOnly, Category=Flag)
	USceneComponent* DropFlagSocket;

	ACTFGameMode* GameMode;
};
