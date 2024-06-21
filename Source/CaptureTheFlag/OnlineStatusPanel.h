// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineStatusPanel.generated.h"

class UVerticalBox;
class UButton;
class UPlayerListPanel;
class UDataTable;

/**
 * 
 */
UCLASS(Abstract)
class CAPTURETHEFLAG_API UOnlineStatusPanel : public UUserWidget
{
	GENERATED_BODY()
public:

	/** Toggles the panel visibility and configures the correct interaction mode */
	void TogglePanelVisibility();

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

protected:

	/** Data Table reference */
	UPROPERTY(EditDefaultsOnly, Category = Data)
	TSoftObjectPtr<UDataTable> PlayerOnlineStatusDataSource;

private:

	/** Fills in the Player List widgets with the data obtained from the Data Table */
	void PopulatePlayerLists();

	/** Opens the panel and configures the correct interaction mode */
	void OpenPanel();

	/** Closes the panel and configures the correct interaction mode */
	UFUNCTION()
	void ClosePanel();

private:

	UPROPERTY(meta = (BindWidget))
	UButton* ClosePanelButton;

	UPROPERTY(meta = (BindWidget))
	UPlayerListPanel* OnlinePlayerListPanel;

	UPROPERTY(meta = (BindWidget))
	UPlayerListPanel* OfflinePlayerListPanel;
	
};
