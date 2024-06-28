// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerOnlineData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerNotificationToast.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API UPlayerNotificationToast : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeWithData(const FPlayerOnlineData& PlayerData);

	float GetDisplayTime() const { return DisplayTime; }

protected:

	UPROPERTY(EditAnywhere, Category = Setup)
	TSoftObjectPtr<UTexture2D> OnlineIcon;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSoftObjectPtr<UTexture2D> OfflineIcon;

	UPROPERTY(EditAnywhere, Category = Setup)
	float DisplayTime = 3.f;

private:

	UPROPERTY(meta = (BindWidget))
	UImage* OnlineStatusImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OnlineStatusLabel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NicknameLabel;
};
