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
UCLASS(Abstract, meta=(DisableNativeTick))
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
	UFUNCTION(BlueprintImplementableEvent, Category = Viewmodel)
	void SetPlayerViewModelObject(const UPlayerViewModel* InPlayerViewModel);

protected:

	virtual void NativeOnInitialized() override;

public:

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InPlayerToastAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OutPlayerToastAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPlayerNotificationToast* PlayerNotificationToast;

	/* Disabling this BindWidget approach because its not compatible with UE's MVVM
	 * This would work by simply subscribing to events on the viewmodel and updating
	 * the widget's values here or calling update methods from the viewmodel.
	 * Instead, this is being setup in the Editor, the viewmodel provides functions
	 * that only get called when the respective value has changed, and we can then
	 * bind the widgets to these functions (or properties)
	 * 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCTFProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrit, meta = (BindWidget))
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

	UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MatchTimerLabel;

	*/

private:
	/* Disabling the update methods (this corresponds to the BindWidget approach explained
	 * above.
	 *
	void UpdateTeamNames();

	void UpdateTeamScore(const ETeamId& TeamId);

	void UpdateTeamMaxScores();
	*/

	UFUNCTION()
	void OnInToastAnimationFinished();

private:

	ACTFGameState* GameState = nullptr;
	ACTFGameMode* GameMode = nullptr;

	FNumberFormattingOptions FloatFormatOptions;

};
