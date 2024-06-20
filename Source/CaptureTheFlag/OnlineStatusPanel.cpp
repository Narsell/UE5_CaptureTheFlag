// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineStatusPanel.h"
#include "PlayerListPanel.h"
#include "PlayerOnlineData.h"
#include "PlayerOnlineDataHolder.h"

void UOnlineStatusPanel::NativePreConstruct()
{
	OnlinePlayerListPanel->SetPanelType(EPlayerListPanelType::ONLINE);
	OfflinePlayerListPanel->SetPanelType(EPlayerListPanelType::OFFLINE);
}

void UOnlineStatusPanel::NativeConstruct()
{
	FString Context;
	TArray<FPlayerOnlineData*> PlayerStatusList;

	if (!PlayerOnlineStatusDataSource) return;

	PlayerOnlineStatusDataSource->GetAllRows<FPlayerOnlineData>(Context, PlayerStatusList);
	for (const FPlayerOnlineData* PlayerStatus: PlayerStatusList) 
	{
		UPlayerOnlineDataHolder* DataHolder = NewObject<UPlayerOnlineDataHolder>();
		DataHolder->InitializeData(PlayerStatus);

		if (PlayerStatus->IsOnline) 
		{
			OnlinePlayerListPanel->AddPlayerEntry(DataHolder);
		}
		else 
		{
			OfflinePlayerListPanel->AddPlayerEntry(DataHolder);
		}
	}
}
