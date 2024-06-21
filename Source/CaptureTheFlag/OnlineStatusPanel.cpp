// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineStatusPanel.h"
#include "PlayerListPanel.h"
#include "PlayerOnlineData.h"
#include "PlayerOnlineDataHolder.h"
#include "Components/Button.h"

void UOnlineStatusPanel::NativePreConstruct()
{
	OnlinePlayerListPanel->SetPanelType(EPlayerListPanelType::ONLINE);
	OfflinePlayerListPanel->SetPanelType(EPlayerListPanelType::OFFLINE);
}

void UOnlineStatusPanel::NativeConstruct()
{
	PopulatePlayerLists();

	ClosePanelButton->OnClicked.AddDynamic(this, &UOnlineStatusPanel::ClosePanel);
}

void UOnlineStatusPanel::PopulatePlayerLists()
{
	FString Context;
	TArray<FPlayerOnlineData*> PlayerStatusList;

	if (!PlayerOnlineStatusDataSource) return;

	PlayerOnlineStatusDataSource->GetAllRows<FPlayerOnlineData>(Context, PlayerStatusList);
	for (const FPlayerOnlineData* PlayerStatus : PlayerStatusList)
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

void UOnlineStatusPanel::OpenPanel()
{

	FInputModeGameAndUI InputGameAndUIMode;
	GetOwningPlayer()->SetInputMode(InputGameAndUIMode);
	GetOwningPlayer()->SetShowMouseCursor(true);
	SetVisibility(ESlateVisibility::Visible);
}

void UOnlineStatusPanel::ClosePanel()
{
	FInputModeGameOnly InputGameMode;
	GetOwningPlayer()->SetInputMode(InputGameMode);
	GetOwningPlayer()->SetShowMouseCursor(false);
	SetVisibility(ESlateVisibility::Hidden);

}

void UOnlineStatusPanel::TogglePanelVisibility()
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		ClosePanel();
	}
	else
	{
		OpenPanel();
	}
}

