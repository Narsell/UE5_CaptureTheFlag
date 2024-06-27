// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h" 
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CTFHud.generated.h"

class UPlayerHud;
class UOnlineStatusPanel;
class UPlayerEntryTooltip;
class UPlayerViewModel;
class UMatchViewModel;
class UOnlineStatusViewModel;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API ACTFHud : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Returns the pointer to the PlayerEntryTooltip widget */
	UPlayerEntryTooltip* GetPlayerEntryTooltipWidget() const { return PlayerEntryTooltip; }

	/** Returns the pointer to the OnlineStatusPanel widget */
	UOnlineStatusPanel* GetOnlineStatusPanelWidget() const { return OnlineStatusPanel; }

	/** Toggles the visibility of the Online Status Panel widget, from visible to hidden and back */
	void ToggleOnlineStatusPanelVisibility();

private:

	/** Initializes and sets the viewmodels to their respective widgets */
	void InitializeViewModels();

private:

	/** WIDGET CLASSES */

	/** Player UMG widget HUD class */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UPlayerHud> PlayerHudClass;

	/** Online status panel class */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UOnlineStatusPanel> OnlineStatusPanelClass;

	/** Online status panel class */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UPlayerEntryTooltip> PlayerEntryTooltipClass;

	/** REFERENCES */

	/** Pointer to Player HUD widget */
	UPROPERTY()
	UPlayerHud* PlayerHud = nullptr;

	/** Pointer to Online Status Panel widget */
	UPROPERTY()
	UOnlineStatusPanel* OnlineStatusPanel = nullptr;

	/** Pointer to Player Entry tooltip widget */
	UPROPERTY()
	UPlayerEntryTooltip* PlayerEntryTooltip = nullptr;

	/** Pointer to owning Player Controller */
	APlayerController* PlayerController = nullptr;

	/** VIEWMODELS */

	UPROPERTY()
	UPlayerViewModel* PlayerViewModel;
	UPROPERTY()
	UMatchViewModel* MatchViewModel;
	UPROPERTY()
	UOnlineStatusViewModel* OnlineStatusViewModel;

	/** GENERAL SETTINGS */

	/** Initial visibility state of the Online Status panel widget */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	ESlateVisibility OnlineStatusInitialState = ESlateVisibility::Hidden;

};
