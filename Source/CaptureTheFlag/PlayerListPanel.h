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
UCLASS(Abstract, meta = (DisableNativeTick))
class CAPTURETHEFLAG_API UPlayerListPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Adds a player entry to this panel's list view */
	void AddPlayerEntry(UObject* Data);

	/** Remove a player entry from this panel's list view */
	void RemovePlayerEntry(UObject* Data);

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

	/**
	 * Set a custom title color for this panel, overrides the default one.
	 * By default the panel color title will be white regardless of the panel type.
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Setup)
	FColor CustomColor = FColor::White;

private:

	/** Toggles the list view visibility from visible to collapsed and back */
	UFUNCTION()
	void ToggleListViewCollapse();

	/** Updates the PlayerListCountLabel with the given amount */
	void UpdatePlayerListCountLabel();

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SectionTitleLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerListCountLabel;

	UPROPERTY(meta = (BindWidget))
	UButton* CollapseButton;

	UPROPERTY(meta = (BindWidget))
	UListView* PlayerListView;

	UPROPERTY()
	TArray<UObject*> DataObjectList;

	int32 PlayerListCount = 0;


};
