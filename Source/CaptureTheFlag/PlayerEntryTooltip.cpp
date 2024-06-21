// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEntryTooltip.h"
#include "PlayerOnlineData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UPlayerEntryTooltip::SetPlayerData(const FPlayerOnlineData* PlayerData)
{
	if (PlayerData)
	{
		NicknameLabel->SetText(FText::FromName(PlayerData->Nickname));
		LevelLabel->SetText(FText::AsNumber(PlayerData->Level));
		IconImage->SetBrushFromSoftTexture(PlayerData->Icon);

		FText OnlineStatusText = FText::FromString(PlayerData->IsOnline ? OnlineText : OfflineText);
		OnlineStatusLabel->SetText(OnlineStatusText);

		TSoftObjectPtr<UTexture2D> OnlineStatusTexture = PlayerData->IsOnline ? OnlineIcon : OfflineIcon;
		if (OnlineStatusTexture.IsValid())
		{
			OnlineStatusImage->SetBrushFromSoftTexture(OnlineStatusTexture);
		}
	}
}
