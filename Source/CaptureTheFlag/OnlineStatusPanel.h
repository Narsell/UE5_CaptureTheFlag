// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineStatusPanel.generated.h"

class UVerticalBox;
class UPlayerListPanel;
class UDataTable;

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UOnlineStatusPanel : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = Data)
	UDataTable* PlayerOnlineStatusDataSource;

private:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	UPlayerListPanel* OnlinePlayerListPanel;

	UPROPERTY(meta = (BindWidget))
	UPlayerListPanel* OfflinePlayerListPanel;
	
};
