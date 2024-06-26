// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFHud.h"
#include "PlayerHud.h"
#include "PlayerEntryTooltip.h"
#include "OnlineStatusPanel.h"
#include "CaptureTheFlagCharacter.h"
#include "CTFGameMode.h"
#include "Kismet/GameplayStatics.h"

void ACTFHud::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerHudClass || !OnlineStatusPanelClass || !PlayerEntryTooltipClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Widget classes have not been set in the player controller blueprint"))
		return;
	}

	PlayerController = GetOwningPlayerController();
	if (!PlayerController) return;

	PlayerHud = CreateWidget<UPlayerHud>(PlayerController, PlayerHudClass);
	if (PlayerHud)
	{
		PlayerHud->AddToViewport();
		SetPlayerHudViewModels();
	}

	OnlineStatusPanel = CreateWidget<UOnlineStatusPanel>(PlayerController, OnlineStatusPanelClass);
	if (OnlineStatusPanel)
	{
		OnlineStatusPanel->SetVisibility(OnlineStatusInitialState);
		OnlineStatusPanel->AddToViewport();
	}

	PlayerEntryTooltip = CreateWidget<UPlayerEntryTooltip>(PlayerController, PlayerEntryTooltipClass);
}

void ACTFHud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTFHud::ToggleOnlineStatusPanelVisibility()
{
	if (OnlineStatusPanel)
	{
		OnlineStatusPanel->TogglePanelVisibility();
	}
}

void ACTFHud::SetPlayerHudViewModels()
{
	if (ACaptureTheFlagCharacter* PlayerCharacter = Cast<ACaptureTheFlagCharacter>(PlayerController->GetPawn()); PlayerCharacter)
	{
		const UPlayerViewModel* PlayerViewModel = PlayerCharacter->GetPlayerViewModel();
		PlayerHud->SetPlayerViewModelObject(PlayerViewModel);
	}

	if (ACTFGameMode* GameMode = Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(this)); GameMode)
	{
		const UMatchViewModel* MatchViewModel = GameMode->GetMatchViewModel();
		PlayerHud->SetMatchViewModelObject(MatchViewModel);

	}
}
