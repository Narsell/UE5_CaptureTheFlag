// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MatchViewModel.generated.h"

class ACTFGameMode;
class ACTFHud;
/**
 *
 */
UCLASS()
class CAPTURETHEFLAG_API UMatchViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	/** Sets the initial state on the view based on the initial model state */
	void Initialize(const ACTFHud* Hud);

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetTeamAName() const { return FText::FromName(TeamA.Name); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetTeamBName() const { return FText::FromName(TeamB.Name); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetTeamAScore() const { return FText::AsNumber(TeamA.Score); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetTeamBScore() const { return FText::AsNumber(TeamB.Score); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FSlateColor GetTeamAColor() const { return TeamA.Color; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FSlateColor GetTeamBColor() const { return TeamB.Color; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetMaxTeamScore() const { return FText::AsNumber(MaxTeamScore); }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetMatchRemainingTime() const { return FText::AsNumber(MatchRemainingTime, &FloatFormatOptions); }

	void SetTeam(const ETeamId TeamId, const FTeam& NewTeam);
	void SetTeamColor(const ETeamId TeamId, const FColor& NewColor);
	void SetTeamName(const ETeamId TeamId, const FName& NewName);
	UFUNCTION()
	void SetTeamScore(const ETeamId TeamId, int32 NewScore);
	void SetMaxTeamScore(int32 NewMaxScore);
	void SetMatchRemainingTime(float NewRemainingTime);

private:

	/** Updates the view match timer, called by TimerManager */
	void OnUpdateMatchTimer();

private:

	FTeam TeamA;
	FTeam TeamB;

	int32 MaxTeamScore;

	float MatchRemainingTime;

	FTimerHandle MatchTimerUpdateHandle;

	FNumberFormattingOptions FloatFormatOptions;

	ACTFGameMode* GameMode = nullptr;
	ACTFGameState* GameState = nullptr;

};
