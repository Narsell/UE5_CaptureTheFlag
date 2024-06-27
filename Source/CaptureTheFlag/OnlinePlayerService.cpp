// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlinePlayerService.h"
#include "PlayerOnlineData.h"
#include "PlayerOnlineDataHolder.h"
#include "OnlineStatusViewModel.h"


void UOnlinePlayerService::StartService(UWorld* World)
{
	// Load data from data-table into objects
	UDataTable* PlayerOnlineStatusDataSource = LoadObject<UDataTable>(this, TEXT("/Game/Core/Data/DT_PlayerOnlineDataSource.DT_PlayerOnlineDataSource"));

	if (!PlayerOnlineStatusDataSource) return;

	FString Context;
	TArray<FPlayerOnlineData*> PlayerDataList;
	PlayerOnlineStatusDataSource->GetAllRows<FPlayerOnlineData>(Context, PlayerDataList);

	for (FPlayerOnlineData* PlayerData : PlayerDataList)
	{
		UPlayerOnlineDataHolder* PlayerDataObject = NewObject<UPlayerOnlineDataHolder>();
		PlayerDataObject->InitializeData(PlayerData);
		PlayerDataObjectList.Add(PlayerDataObject);
		if (PlayerData->IsOnline)
		{
			++OnlinePlayers;
		}
	}

	if (World)
	{
		World->GetTimerManager().SetTimer(RandomChangeStatusHandle, this, &UOnlinePlayerService::ChangeRandomPlayerStatus, 2.f, true);
	}

}

UOnlinePlayerService::~UOnlinePlayerService()
{
	UE_LOG(LogTemp, Error, TEXT("Destroying online service"))
}

const TArray<UPlayerOnlineDataHolder*>& UOnlinePlayerService::GetPlayerList()
{
	return PlayerDataObjectList;
}

void UOnlinePlayerService::ChangeRandomPlayerStatus()
{
	int32 RandomIndex = FMath::Rand() % PlayerDataObjectList.Num();
	FPlayerOnlineData* Data = PlayerDataObjectList[RandomIndex]->GetData();
	Data->IsOnline = !Data->IsOnline;

	OnlinePlayers = Data->IsOnline ? OnlinePlayers + 1 : OnlinePlayers - 1;

	PlayerStatusChangeDelegate.Broadcast(PlayerDataObjectList[RandomIndex]);

}