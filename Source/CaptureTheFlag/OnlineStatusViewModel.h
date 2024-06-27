// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineStatusViewModel.generated.h"

class UPlayerOnlineDataHolder;
class UOnlinePlayerService;
class UOnlineStatusPanel;
class ACTFHud;

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UOnlineStatusViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UOnlineStatusViewModel();

	/** Sets the initial state on the view based on the initial model state */
	void Initialize(const ACTFHud* Hud);

	UFUNCTION()
	void OnPlayerStatusChange(UPlayerOnlineDataHolder* PlayerOnlineObject);

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetTotalPlayers() const { return FText::AsNumber(TotalPlayers); }

private:
	
	int32 TotalPlayers;

	TArray<UPlayerOnlineDataHolder*> PlayerDataObjectList;

	/** Pointer to Online Player Service (model) */
	UPROPERTY()
	UOnlinePlayerService* OnlinePlayerService;

	/** Pointer to Online Status Widget (view) */
	UOnlineStatusPanel* OnlineStatusPanelWidget = nullptr;


};
