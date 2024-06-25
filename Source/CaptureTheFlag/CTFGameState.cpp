// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFGameState.h"

ACTFGameState::ACTFGameState()
	:
	TeamA({"Team A", 0, FColor::Green}),
	TeamB({"Team B", 0, FColor::Red})
{
}

const FTeam& ACTFGameState::GetTeam(const ETeamId& TeamId) const
{
	return TeamId == ETeamId::A ? TeamA : TeamB;
}

int32 ACTFGameState::AddScoreToTeam(const ETeamId& TeamId)
{
	FTeam& Team = TeamId == ETeamId::A ? TeamA : TeamB;
	++Team.Score;
	return Team.Score;
}

