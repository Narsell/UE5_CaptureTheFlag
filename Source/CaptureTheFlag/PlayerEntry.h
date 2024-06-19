// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "PlayerOnlineData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEntry.generated.h"

class UTextBlock;
class UImage;

/**
 * Player Entry class meant to be used in a ListView.
 * InitializeWithData should be called OnListItemObjectSet event on child BP (From UserObjectListEntry interface)
 */
UCLASS()
class CAPTURETHEFLAG_API UPlayerEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	/**  Sets all the UI elements from the values passed in PlayerData */
	UFUNCTION(BlueprintCallable, Category=Initialization)
	void InitializeWithData(const FPlayerOnlineData& PlayerData);

private:

	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Nickname;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Level;

};
