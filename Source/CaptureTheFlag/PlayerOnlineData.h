// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerOnlineData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerOnlineData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FPlayerOnlineData()
		:
		Nickname(""),
		Level(0),
		IsOnline(false)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Nickname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOnline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;
};
