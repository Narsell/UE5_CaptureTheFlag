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
class UCTFProgressBar;
class UTextBlock;
class UPlayerOnlineDataHolder;
class UPlayerNotificationToast;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Displays the friend notification toast with the information given in the player online data object */
	void OnFriendStatusNotification(UPlayerOnlineDataHolder* PlayerOnlineObject);

	/** Blueprint event that gets fired when the match view-model is ready to be set into the widget */
	UFUNCTION(BlueprintImplementableEvent, Category=Viewmodel)
	void SetMatchViewModelObject(const UMatchViewModel* InMatchViewModel);
	
	/** Blueprint event that gets fired when the player view-model is ready to be set into the widget */
	UFUNCTION(BlueprintImplementableEvent, Category=Viewmodel)
	void SetPlayerViewModelObject(const UPlayerViewModel* InPlayerViewModel);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:

	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InPlayerToastAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OutPlayerToastAnimation;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPlayerNotificationToast* PlayerNotificationToast;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCTFProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCTFProgressBar* StaminaBar;

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

	UFUNCTION()
	void OnInToastAnimationFinished();

private:

	ACTFGameState* GameState = nullptr;
	ACTFGameMode* GameMode = nullptr;

	FNumberFormattingOptions FloatFormatOptions;

};
