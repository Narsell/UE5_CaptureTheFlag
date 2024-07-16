// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CTFGameState.generated.h"

UENUM(BlueprintType)
enum class ETeamId : uint8 {
	A,
	B,
	NONE
};

USTRUCT(BlueprintType, Category=Teams)
struct FTeam {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ETeamId TeamId = ETeamId::NONE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName Name = "Team X";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Score = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FColor Color = FColor::Magenta;

	bool operator==(const FTeam& Other) {
		return TeamId == Other.TeamId;
	}
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
	 * Adds a score point to the team that matches the given ID and returns the new score.
	 */
	int32 AddScoreToTeam(const ETeamId& TeamId);

protected:

	// TODO: Store these in an unordered_map with keys as teamids and values as FTeam
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Teams)
	FTeam TeamA;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Teams)
	FTeam TeamB;

};
