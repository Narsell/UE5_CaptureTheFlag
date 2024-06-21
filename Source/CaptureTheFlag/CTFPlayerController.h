// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTFPlayerController.generated.h"

class ACTFHud;
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

	/** HUD actor (non-umg one) pointer */
	ACTFHud* HudActor = nullptr;

	/** Toggle Online Menu action */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* ToggleOnlineStatusPanelAction;

};
