// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h" 
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CTFHud.generated.h"

class UPlayerHud;
class UOnlineStatusPanel;
class UPlayerEntryTooltip;
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

	/** Toggles the visibility of the Online Status Panel widget, from visible to hidden and back */
	void ToggleOnlineStatusPanelVisibility();

private:

	/** Sets the necessary view-models onto the player hud widget */
	void SetPlayerHudViewModels();

private:

	/** Player UMG widget HUD class */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UPlayerHud> PlayerHudClass;

	/** Online status panel class */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UOnlineStatusPanel> OnlineStatusPanelClass;

	/** Online status panel class */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UPlayerEntryTooltip> PlayerEntryTooltipClass;

	/** Initial visibility state of the Online Status panel widget */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	ESlateVisibility OnlineStatusInitialState = ESlateVisibility::Hidden;

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
};
