// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerListPanel.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"

void UPlayerListPanel::AddPlayerEntry(UObject* Data)
{
	PlayerListView->AddItem(Data);
}

void UPlayerListPanel::SetPanelType(EPlayerListPanelType NewPanelType)
{
	PanelType = NewPanelType; 
	NativePreConstruct();
}

void UPlayerListPanel::NativePreConstruct()
{

	FString TitleText = PanelType == EPlayerListPanelType::ONLINE ? FString("ONLINE") : FString("OFFLINE");
	if (!CustomTitle.IsEmpty()) 
	{
		TitleText = CustomTitle;
	}
	SectionTitleLabel->SetText(FText::FromString(TitleText));
}

void UPlayerListPanel::NativeConstruct()
{

	CollapseButton->OnClicked.AddDynamic(this, &UPlayerListPanel::ToggleListViewCollapse);
}

void UPlayerListPanel::ToggleListViewCollapse()
{
	ESlateVisibility NewVisibility = PlayerListView->GetVisibility() == ESlateVisibility::Visible ? ESlateVisibility::Collapsed : ESlateVisibility::Visible;
	PlayerListView->SetVisibility(NewVisibility);
}
