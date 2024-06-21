// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "PlayerOnlineDataHolder.h"
#include "CTFHud.h"
#include "PlayerEntryTooltip.h"

void UPlayerEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Border->ToolTipWidgetDelegate.BindUFunction(this, "GetTooltipWidget");
}

void UPlayerEntry::NativePreConstruct()
{
	BorderNormalColor = Border->GetBrushColor().ToFColor(true);
}

void UPlayerEntry::InitializeWithData(UObject* InObject)
{
	UPlayerOnlineDataHolder* PlayerDataHolder = Cast<UPlayerOnlineDataHolder>(InObject);
	if (!PlayerDataHolder) return;

	PlayerData = PlayerDataHolder->GetData();

	if (PlayerData)
	{
		NicknameLabel->SetText(FText::FromName(PlayerData->Nickname));
		LevelLabel->SetText(FText::AsNumber(PlayerData->Level));
		IconImage->SetBrushFromSoftTexture(PlayerData->Icon);
	}
}

void UPlayerEntry::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Border->SetBrushColor(BorderHighlightColor);
}

void UPlayerEntry::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Border->SetBrushColor(BorderNormalColor);
}

UWidget* UPlayerEntry::GetTooltipWidget()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (!PlayerController) return nullptr;

	ACTFHud* Hud = Cast<ACTFHud>(PlayerController->GetHUD());

	if (Hud)
	{
		UPlayerEntryTooltip* TooltipWidget = Hud->GetPlayerEntryTooltipWidget();
		if (TooltipWidget)
		{
			TooltipWidget->SetPlayerData(PlayerData);
			return TooltipWidget;
		}
	}
	return nullptr;

}

