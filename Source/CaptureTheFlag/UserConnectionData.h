// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserConnectionData.generated.h"

USTRUCT(BlueprintType)
struct FUserConnectionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FUserConnectionData()
		:
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
	TSoftObjectPtr<UTexture> Icon;
};
