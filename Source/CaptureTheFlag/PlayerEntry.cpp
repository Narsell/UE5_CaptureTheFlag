// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerOnlineDataHolder.h"


void UPlayerEntry::InitializeWithData(UObject* InObject)
{
	UPlayerOnlineDataHolder* PlayerDataHolder = Cast<UPlayerOnlineDataHolder>(InObject);
	if (!PlayerDataHolder) return;

	const FPlayerOnlineData* PlayerData = PlayerDataHolder->GetData();

	if (PlayerData) {
		NicknameLabel->SetText(FText::FromName(PlayerData->Nickname));
		LevelLabel->SetText(FText::AsNumber(PlayerData->Level));
		IconImage->SetBrushFromSoftTexture(PlayerData->Icon);
	}

}
