// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEntryTooltip.generated.h"

class UTextBlock;
class UImage;
struct FPlayerOnlineData;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API UPlayerEntryTooltip : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Sets the player data onto this player's tooltip properties */
	void SetPlayerData(const FPlayerOnlineData* PlayerData);

private:

	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NicknameLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OnlineStatusLabel;

	UPROPERTY(meta = (BindWidget))
	UImage* OnlineStatusImage;

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	FString OnlineText = FString("Online");

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	FString OfflineText = FString("Offline");

	/** Soft obj pointer to online icon 2D texture */
	UPROPERTY(EditDefaultsOnly, Category=Setup)
	TSoftObjectPtr<UTexture2D> OnlineIcon;

	/** Soft obj pointer to offline icon 2D texture */
	UPROPERTY(EditDefaultsOnly, Category=Setup)
	TSoftObjectPtr<UTexture2D> OfflineIcon;
	
};
