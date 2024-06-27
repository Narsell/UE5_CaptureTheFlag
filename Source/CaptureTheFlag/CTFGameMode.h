// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CTFGameMode.generated.h"

class UMatchViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamScoreSignature, ETeamId, TeamId, int32, NewScore);

/**
 *
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ACTFGameMode();

	UPROPERTY(BlueprintAssignable)
	FOnTeamScoreSignature TeamScoreDelegate;

	/** Returns the required score to win */
	int32 GetRequiredScoreToWin() const { return ScoreToWin; };

	/** Returns the remainig seconds for the match to finish */
	float GetRemainingMatchTime() const { return GetWorldTimerManager().GetTimerRemaining(MatchTimerHandle); }

	/**
	 * Registers a score by the team given by the TeamId.
	 * This will also handle scenarios such as ties, wins, extra time
	 */
	void OnTeamScored(const ETeamId& TeamId);

protected:

	virtual void BeginPlay() override;

	/** Required score to win */
	UPROPERTY(EditAnywhere, Category=Rules)
	int32 ScoreToWin = 3;

	/** Match time length in seconds */
	UPROPERTY(EditAnywhere, Category=Rules)
	float MatchTimeSeconds = 300.f;

	/** Extra match time in seconds */
	UPROPERTY(EditAnywhere, Category = Rules)
	float ExtraTimeSeconds = MatchTimeSeconds / 2.f;

private:

	void MatchTimerEnd();

private:

	/* Determines if an extra time has already been added to the time match once **/
	bool bHasExtraTimeHappened = false;

	ACTFGameState* GameState = nullptr;

	FTimerHandle MatchTimerHandle;

};
