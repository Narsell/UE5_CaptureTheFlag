// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CTFGameState.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

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

protected:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHealthLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamANameLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamBNameLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamAScoreLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamBScoreLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamAMaxScoreLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamBMaxScoreLabel;

private:

	/** Updates the current health values on the HUD with the NewHealth provided. */
	void UpdateCurrentHealth(float NewHealth);

	/** Updates the maximum health values on the HUD with the NewMaxHealth provided. */
	void UpdateMaxHealth(float NewMaxHealth);

	/** Updates the team name labels on the HUD with the current names set on the Game State */
	void UpdateTeamNames();

	/** Updates a team's score label on the HUD with the NewScore provided */
	void UpdateTeamScore(const ETeamId& TeamId);

	/** Updates the teams max score labels on the HUD with the current names set on the Game State */
	void UpdateTeamMaxScores();


private:

	ACTFPlayerState* PlayerState = nullptr;
	ACTFGameState* GameState = nullptr;
	ACTFGameMode* GameMode = nullptr;

	FNumberFormattingOptions HealthFormatOptions;
	
};
