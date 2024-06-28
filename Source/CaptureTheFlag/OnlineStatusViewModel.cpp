// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineStatusViewModel.h"
#include "PlayerOnlineData.h"
#include "PlayerOnlineDataHolder.h"
#include "OnlineStatusPanel.h"
#include "OnlinePlayerService.h"
#include "CTFHud.h"
#include "PlayerHud.h"

UOnlineStatusViewModel::UOnlineStatusViewModel()
	:
	OnlinePlayerService(NewObject<UOnlinePlayerService>())
{
}

void UOnlineStatusViewModel::Initialize(const ACTFHud* Hud)
{
	if (OnlinePlayerService)
	{
		// Starting service/model (holds and updates data)
		OnlinePlayerService->StartService(Hud->GetWorld());
		PlayerDataObjectList = OnlinePlayerService->GetPlayerList();
		OnlinePlayerService->PlayerStatusChangeDelegate.AddDynamic(this, &UOnlineStatusViewModel::OnPlayerStatusChange);
	}

	// Setting widget reference (view)
	PlayerHudWidget = Hud->GetPlayerHudWidget();
	OnlineStatusPanelWidget = Hud->GetOnlineStatusPanelWidget();

	if (OnlineStatusPanelWidget)
	{
		OnlineStatusPanelWidget->InitializePlayerList(PlayerDataObjectList);
	}

	SetTotalPlayers();
}

void UOnlineStatusViewModel::OnPlayerStatusChange(UPlayerOnlineDataHolder* PlayerOnlineObject)
{
	if (!PlayerOnlineObject)
	{
		return;
	}
	if (OnlineStatusPanelWidget)
	{
		OnlineStatusPanelWidget->OnPlayerStatusChange(PlayerOnlineObject);
	}
	if (PlayerHudWidget)
	{
		PlayerHudWidget->OnFriendStatusNotification(PlayerOnlineObject);
	}
}

void UOnlineStatusViewModel::SetTotalPlayers()
{
	TotalPlayers = PlayerDataObjectList.Num();
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTotalPlayers);
}