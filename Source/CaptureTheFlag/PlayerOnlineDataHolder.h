// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerOnlineData.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerOnlineDataHolder.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UPlayerOnlineDataHolder : public UObject
{
	GENERATED_BODY()

public:

	void InitializeData(const FPlayerOnlineData* InPlayerOnlineData) { PlayerOnlineData = InPlayerOnlineData; }

	const FPlayerOnlineData* GetData() const { return PlayerOnlineData; }

private:

	const FPlayerOnlineData* PlayerOnlineData;
	
};
