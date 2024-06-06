// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CTFGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ACTFGameMode();

	/**
	 * Registers a score by the team given by the TeamId.
	 * This will also handle scenarios such as ties, wins, extra time, etc...
	 */
	void OnTeamScored(const ETeamId& TeamId);

protected:

	virtual void BeginPlay() override;

private:

	ACTFGameState* GameState;
	
};
