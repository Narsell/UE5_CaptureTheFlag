// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerOnlineData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEntry.generated.h"

class UTextBlock;
class UImage;
class UBorder;

/**
 * Player Entry class meant to be used in a ListView.
 * InitializeWithData should be called OnListItemObjectSet event on child BP (From UserObjectListEntry interface)
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API UPlayerEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Sets all the UI elements from the values passed in PlayerData */
	UFUNCTION(BlueprintCallable, Category=Initialization)
	void InitializeWithData(UObject* InObject);

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;

private:

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	/** Returns the Tooltip widget with the player data set. */
	UFUNCTION()
	UWidget* GetTooltipWidget();

private:

	UPROPERTY(meta = (BindWidget))
	UBorder* Border;

	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NicknameLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelLabel;

	/** Color the border brush element will take when highlighted */
	UPROPERTY(EditDefaultsOnly, Category=Setup)
	FColor BorderHighlightColor = FColor(255U, 255U, 255U, 51U);

	/** Color the border brush element will take when not-hightlated (normal state) */
	FColor BorderNormalColor;

	/** Pointer to player data corresponding to this player entry */
	const FPlayerOnlineData* PlayerData;

};
