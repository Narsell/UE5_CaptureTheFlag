// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineStatusPanel.generated.h"

class UVerticalBox;
class UButton;
class UPlayerListPanel;
class UPlayerOnlineDataHolder;
class UOnlineStatusViewModel;

/**
 * 
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class CAPTURETHEFLAG_API UOnlineStatusPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Updates a player online status (changes its list view parent widget) */
	void OnPlayerStatusChange(UPlayerOnlineDataHolder* PlayerDataObject);

	/** Fills in the Player List widgets with the data obtained from the Data Table */
	void InitializePlayerList(const TArray<UPlayerOnlineDataHolder*>& PlayerObjectDataList);

	/** Toggles the panel visibility and configures the correct interaction mode */
	void TogglePanelVisibility();

	/** Blueprint event that gets fired when the online status view-model is ready to be set into the widget */
	UFUNCTION(BlueprintImplementableEvent, Category = Viewmodel)
	void SetOnlineStatusViewModelObject(const UOnlineStatusViewModel* InOnlineStatusViewModel);

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ClosePanelButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPlayerListPanel* OnlinePlayerListPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPlayerListPanel* OfflinePlayerListPanel;

private:

	/** Opens the panel and configures the correct interaction mode */
	void OpenPanel();

	/** Closes the panel and configures the correct interaction mode */
	UFUNCTION()
	void ClosePanel();

	
};
