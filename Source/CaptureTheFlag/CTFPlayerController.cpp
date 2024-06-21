// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFPlayerController.h"
#include "PlayerHud.h"
#include "OnlineStatusPanel.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

void ACTFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerWidgets();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if(!ToggleOnlineStatusPanelAction)
		UE_LOG(LogTemp, Error, TEXT("Input action has not been set in the player controller blueprint"))
	EnhancedInputComponent->BindAction(ToggleOnlineStatusPanelAction, ETriggerEvent::Triggered, this, &ACTFPlayerController::ToggleOnlineStatusPanelVisibility);

}

void ACTFPlayerController::CreatePlayerWidgets()
{
	if (!PlayerHudClass || !OnlineStatusPanelClass) {
		UE_LOG(LogTemp, Error, TEXT("Widget classes have not been set in the player controller blueprint"))
		return;
	}

	PlayerHud = CreateWidget<UPlayerHud>(this, PlayerHudClass);
	if (PlayerHud)
	{
		PlayerHud->AddToViewport();
	}

	OnlineStatusPanel = CreateWidget<UOnlineStatusPanel>(this, OnlineStatusPanelClass);
	if (OnlineStatusPanel)
	{
		OnlineStatusPanel->SetVisibility(OnlineStatusInitialState);
		OnlineStatusPanel->AddToViewport();
	}
}

void ACTFPlayerController::ToggleOnlineStatusPanelVisibility()
{
	if (OnlineStatusPanel)
	{
		OnlineStatusPanel->TogglePanelVisibility();
	}
}
