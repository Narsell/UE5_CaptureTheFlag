// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFHud.h"
#include "PlayerHud.h"
#include "PlayerEntryTooltip.h"
#include "OnlineStatusPanel.h"
#include "CaptureTheFlagCharacter.h"
#include "CTFGameMode.h"
#include "PlayerViewModel.h"
#include "MatchViewModel.h"
#include "OnlineStatusViewModel.h"

void ACTFHud::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	const TCHAR* FunctionName = ANSI_TO_TCHAR(__FUNCTION__);

	if (!PlayerHudClass || !OnlineStatusPanelClass || !PlayerEntryTooltipClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Widget classes have not been set in the map BP_HUD blueprint"), FunctionName)
		return;
	}

	PlayerController = GetOwningPlayerController();
	if (!PlayerController) return;

	PlayerHud = CreateWidget<UPlayerHud>(PlayerController, PlayerHudClass);
	if (PlayerHud)
	{
		PlayerHud->AddToViewport();
	}

	OnlineStatusPanel = CreateWidget<UOnlineStatusPanel>(PlayerController, OnlineStatusPanelClass);
	if (OnlineStatusPanel)
	{
		OnlineStatusPanel->SetVisibility(OnlineStatusInitialState);
		OnlineStatusPanel->AddToViewport();
	}

	PlayerEntryTooltip = CreateWidget<UPlayerEntryTooltip>(PlayerController, PlayerEntryTooltipClass);

	InitializeViewModels();

}

void ACTFHud::ToggleOnlineStatusPanelVisibility()
{
	if (OnlineStatusPanel)
	{
		OnlineStatusPanel->TogglePanelVisibility();
	}
}

void ACTFHud::InitializeViewModels()
{
	PlayerViewModel = NewObject<UPlayerViewModel>();
	MatchViewModel = NewObject<UMatchViewModel>();
	OnlineStatusViewModel = NewObject<UOnlineStatusViewModel>();

	if (PlayerViewModel)
	{
		PlayerViewModel->Initialize(this);
		PlayerHud->SetPlayerViewModelObject(PlayerViewModel);
	}

	if (MatchViewModel)
	{
		MatchViewModel->Initialize(this);
		PlayerHud->SetMatchViewModelObject(MatchViewModel);
	}

	if (OnlineStatusViewModel)
	{
		OnlineStatusViewModel->Initialize(this);
		OnlineStatusPanel->SetOnlineStatusViewModelObject(OnlineStatusViewModel);
	}
}
