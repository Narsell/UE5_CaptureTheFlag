// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

class ACaptureTheFlagCharacter;
class UMatchViewModel;
class UPlayerViewModel;
class ACTFPlayerState;
class ACTFGameMode;
class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Blueprint event that gets fired when the match view-model is ready to be set into the widget */
	UFUNCTION(BlueprintImplementableEvent, Category=Viewmodel)
	void SetMatchViewModelObject(const UMatchViewModel* InMatchViewModel);
	
	/** Blueprint event that gets fired when the player view-model is ready to be set into the widget */
	UFUNCTION(BlueprintImplementableEvent, Category=Viewmodel)
	void SetPlayerViewModelObject(const UPlayerViewModel* InPlayerViewModel);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentHealthLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxHealthLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentStaminaLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxStaminaLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TeamANameLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TeamBNameLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TeamAScoreLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TeamBScoreLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TeamAMaxScoreLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TeamBMaxScoreLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MatchTimerLabel;

private:

	/** Updates the team name labels on the HUD with the current names set on the Game State */
	void UpdateTeamNames();

	/** Updates a team's score label on the HUD with the NewScore provided */
	void UpdateTeamScore(const ETeamId& TeamId);

	/** Updates the teams max score labels on the HUD with the current names set on the Game State */
	void UpdateTeamMaxScores();


private:

	ACTFGameState* GameState = nullptr;
	ACTFGameMode* GameMode = nullptr;

	FNumberFormattingOptions FloatFormatOptions;

};
