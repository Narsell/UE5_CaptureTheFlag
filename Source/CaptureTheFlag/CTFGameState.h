// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CTFGameState.generated.h"

USTRUCT(BlueprintType, Category=Teams)
struct FTeam {

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName Name = "Default Team";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Points = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FColor Color = FColor::Magenta;
};

UENUM(BlueprintType)
enum class ETeamId : uint8 {
	A,
	B
};

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API ACTFGameState : public AGameState
{
	GENERATED_BODY()

public:
	
	ACTFGameState();

	/** 
	 * Returns the information struct const reference to the team that matches the given ID.
	 */
	UFUNCTION(BlueprintCallable, Category=Teams)
	const FTeam& GetTeam(const ETeamId& TeamId) const;

	/**
	 * Adds a score point to the team that matches the given ID.
	 */
	void AddScoreToTeam(const ETeamId& TeamId);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Teams)
	FTeam TeamA;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Teams)
	FTeam TeamB;

private:

	/**
	 * Returns the information struct reference to the team that matches the given ID.
	 */
	FTeam& GetTeam(const ETeamId& TeamId);
	
};
