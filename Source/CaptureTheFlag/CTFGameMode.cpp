// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFGameMode.h"
#include "Kismet/GameplayStatics.h" 

ACTFGameMode::ACTFGameMode()
	:
	GameState(nullptr)
{
}

void ACTFGameMode::BeginPlay()
{
	GameState = Cast<ACTFGameState>(UGameplayStatics::GetGameState(this));
}

void ACTFGameMode::OnTeamScored(const ETeamId& TeamId)
{
	ensure(GameState);

	if (GameState) {
		GameState->AddScoreToTeam(TeamId);
	}
}

