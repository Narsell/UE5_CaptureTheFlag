// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h" 
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTFPlayerController.generated.h"

class UPlayerHud;
class UOnlineStatusPanel;
class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API ACTFPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	/** Creates Player HUD and Online Status panel widgets */
	void CreatePlayerWidgets();

	/** Toggles the visibility of the Online Status Panel widget, from visible to hidden and back */
	void ToggleOnlineStatusPanelVisibility();

private:

	/** Player HUD class */
	UPROPERTY(EditDefaultsOnly, Category=Widget)
	TSubclassOf<UPlayerHud> PlayerHudClass;

	/** Online status panel class */
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UOnlineStatusPanel> OnlineStatusPanelClass;

	UPROPERTY(EditDefaultsOnly, Category = Widget)
	ESlateVisibility OnlineStatusInitialState = ESlateVisibility::Hidden;

	/** Toggle Online Menu action */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ToggleOnlineStatusPanelAction;



	/** Pointer to Player HUD widget */
	UPlayerHud* PlayerHud = nullptr;

	/** Pointer to Online Status Panel widget */
	UOnlineStatusPanel* OnlineStatusPanel = nullptr;
};
