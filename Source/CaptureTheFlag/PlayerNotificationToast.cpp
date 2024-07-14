// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerNotificationToast.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerOnlineData.h"

void UPlayerNotificationToast::InitializeWithData(const FPlayerOnlineData& PlayerData)
{
	OnlineStatusLabel->SetText(FText::FromString(PlayerData.IsOnline ? "Online" : "Offline"));
	NicknameLabel->SetText(FText::FromName(PlayerData.Nickname));
	OnlineStatusImage->SetBrushFromSoftTexture(PlayerData.IsOnline ? OnlineIcon : OfflineIcon);
}
