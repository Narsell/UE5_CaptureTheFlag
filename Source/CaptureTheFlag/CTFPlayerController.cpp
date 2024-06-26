// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFPlayerController.h"
#include "CTFHud.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "CaptureTheFlagCharacter.h"
#include "HealthComponent.h"

void ACTFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HudActor = Cast<ACTFHud>(GetHUD());

	PlayerCharacter = Cast<ACaptureTheFlagCharacter>(GetPawn());

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	// Toggles online status menu
	EnhancedInputComponent->BindAction(ToggleOnlineStatusPanelAction, ETriggerEvent::Triggered, HudActor, &ACTFHud::ToggleOnlineStatusPanelVisibility);
	
	// Debuging
	EnhancedInputComponent->BindAction(DebugAction_1, ETriggerEvent::Triggered, this, &ACTFPlayerController::DebugReceiveDamage);
}

void ACTFPlayerController::DebugReceiveDamage()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->GetHealthComponent()->TakeDamage(15.f);
	}
}
