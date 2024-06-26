// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTFPlayerController.generated.h"

class ACTFHud;
class UInputAction;
class ACaptureTheFlagCharacter;

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

	void DebugReceiveDamage();

private:


	/** Toggle Online Menu action */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ToggleOnlineStatusPanelAction;

	/** Debug action */
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* DebugAction_1 = nullptr;

	/** Controlled player character pointer */
	ACaptureTheFlagCharacter* PlayerCharacter = nullptr;

	/** HUD actor (non-umg one) pointer */
	ACTFHud* HudActor = nullptr;
};
