// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFPlayerController.h"
#include "CTFHud.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

void ACTFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	HudActor = Cast<ACTFHud>(GetHUD());

	if(!ToggleOnlineStatusPanelAction)
		UE_LOG(LogTemp, Error, TEXT("Input action has not been set in the player controller blueprint"))

	EnhancedInputComponent->BindAction(ToggleOnlineStatusPanelAction, ETriggerEvent::Triggered, HudActor, &ACTFHud::ToggleOnlineStatusPanelVisibility);

}
