// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CTFGameMode.generated.h"

DECLARE_DELEGATE_OneParam(FOnTeamScoreSignature, const ETeamId& TeamId);

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ACTFGameMode();

	FOnTeamScoreSignature OnTeamScoreDelegate;

	int32 GetRequiredScoreToWin() const { return ScoreToWin; };

	/**
	 * Registers a score by the team given by the TeamId.
	 * This will also handle scenarios such as ties, wins, extra time, etc...
	 */
	void OnTeamScored(const ETeamId& TeamId);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category=Rules)
	int32 ScoreToWin = 3;

private:

	ACTFGameState* GameState;
	
};
