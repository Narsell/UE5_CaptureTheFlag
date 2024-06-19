// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerEntry.h"

void UPlayerEntry::InitializeWithData(const FPlayerOnlineData& PlayerData)
{

	Nickname->SetText(FText::FromName(PlayerData.Nickname));
	Level->SetText(FText::AsNumber(PlayerData.Level));
	Icon->SetBrushFromSoftTexture(PlayerData.Icon);
}
