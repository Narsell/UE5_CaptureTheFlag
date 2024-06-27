// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OnlinePlayerService.generated.h"

class UPlayerOnlineDataHolder;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatusChangeSignature, UPlayerOnlineDataHolder*, PlayerDataObject);

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UOnlinePlayerService : public UObject
{
	GENERATED_BODY()

public:

	~UOnlinePlayerService();

	FOnPlayerStatusChangeSignature PlayerStatusChangeDelegate;

	/** Loads data into the service */
	void StartService(UWorld* World);

	/** Returns the player list */
	const TArray<UPlayerOnlineDataHolder*>& GetPlayerList();

	int32 GetOnlinePlayers() const { return OnlinePlayers; }

	int32 GetOfflinePlayers() const { return PlayerDataObjectList.Num() - OnlinePlayers; }

private:


	/** Changes the status from a random player data object and broadcasts the change */
	void ChangeRandomPlayerStatus();

private:

	UPROPERTY()
	TArray<UPlayerOnlineDataHolder*> PlayerDataObjectList;

	FTimerHandle RandomChangeStatusHandle;

	int32 OnlinePlayers;
	
};
