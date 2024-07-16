// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../CTFGameMode.h"
#include "CoreMinimal.h"
#include "GauntletTestController.h"
#include "WinnerTeamController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAutomation, Display, All);


class ACTFGameMode;
/**
 * This Gauntlet controller tests that a team with a higher score wins the match.
 */
UCLASS()
class CAPTURETHEFLAG_API UWinnerTeamController : public UGauntletTestController
{
	GENERATED_BODY()
	
public:

	virtual void OnInit() override;

	virtual void OnPostMapChange(UWorld* World) override;

private:

	UFUNCTION()
	void OnMatchEnd(ETeamId TeamId);

	ETeamId ExpectedWinner = ETeamId::A;

	ACTFGameMode* GameMode = nullptr;
};
