// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerListPanel.generated.h"

UENUM(BlueprintType)
enum class EPlayerListPanelType : uint8
{
	ONLINE,
	OFFLINE
};

class UTextBlock;
class UButton;
class UListView;

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UPlayerListPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Adds a player entry to this panel's list view */
	void AddPlayerEntry(UObject* Data);

	/** Updates the panel type and forces an update via NativePreConstruct */
	void SetPanelType(EPlayerListPanelType NewPanelType);

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=Setup)
	EPlayerListPanelType PanelType = EPlayerListPanelType::ONLINE;

	/**
	 * Set a custom title for this panel, overrides the default one.
	 * By default the panel title will match the Panel Type (Online/Offline)
	 * Leave empty to set the default.
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Setup)
	FString CustomTitle;

private:

	/** Toggles the list view visibility from visible to collapsed and back */
	UFUNCTION()
	void ToggleListViewCollapse();

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SectionTitleLabel;

	UPROPERTY(meta = (BindWidget))
	UButton* CollapseButton;

	UPROPERTY(meta = (BindWidget))
	UListView* PlayerListView;


};
