// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineStatusPanel.h"
#include "PlayerListPanel.h"
#include "PlayerOnlineDataHolder.h"
#include "Components/Button.h"
#include "OnlineStatusViewModel.h"

void UOnlineStatusPanel::NativePreConstruct()
{
	Super::NativePreConstruct();

	OnlinePlayerListPanel->SetPanelType(EPlayerListPanelType::ONLINE);
	OfflinePlayerListPanel->SetPanelType(EPlayerListPanelType::OFFLINE);
}

void UOnlineStatusPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ClosePanelButton->OnClicked.AddDynamic(this, &UOnlineStatusPanel::ClosePanel);
}

void UOnlineStatusPanel::OnPlayerStatusChange(UPlayerOnlineDataHolder* PlayerDataObject)
{
	if (PlayerDataObject->GetData()->IsOnline)
	{
		OfflinePlayerListPanel->RemovePlayerEntry(PlayerDataObject);
		OnlinePlayerListPanel->AddPlayerEntry(PlayerDataObject);
	}
	else
	{
		OnlinePlayerListPanel->RemovePlayerEntry(PlayerDataObject);
		OfflinePlayerListPanel->AddPlayerEntry(PlayerDataObject);
	}
}

void UOnlineStatusPanel::InitializePlayerList(const TArray<UPlayerOnlineDataHolder*>& PlayerObjectDataList)
{

	for (UPlayerOnlineDataHolder* PlayerDataObject : PlayerObjectDataList)
	{
		if (PlayerDataObject->GetData()->IsOnline)
		{
			OnlinePlayerListPanel->AddPlayerEntry(PlayerDataObject);
		}
		else
		{
			OfflinePlayerListPanel->AddPlayerEntry(PlayerDataObject);
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

