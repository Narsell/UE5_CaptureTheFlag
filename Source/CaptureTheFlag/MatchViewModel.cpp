// Fill out your copyright notice in the Description page of Project Settings.

#include "MatchViewModel.h"
#include "TimerManager.h"
#include "CTFGameMode.h"
#include "CTFHud.h"
#include "Kismet/GameplayStatics.h"

void UMatchViewModel::Initialize(const ACTFHud* Hud)
{
	GameMode = Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(Hud));
	GameState = Cast<ACTFGameState>(UGameplayStatics::GetGameState(Hud));

	if (GameMode)
	{
		SetMatchRemainingTime(GameMode->GetRemainingMatchTime());
		SetMaxTeamScore(GameMode->GetRequiredScoreToWin());
		GameMode->TeamScoreDelegate.AddDynamic(this, &UMatchViewModel::SetTeamScore);
		GameMode->GetWorldTimerManager().SetTimer(MatchTimerUpdateHandle, this, &UMatchViewModel::OnUpdateMatchTimer, 1.f, true);
	}
	if (GameState)
	{
		SetTeam(ETeamId::A, GameState->GetTeam(ETeamId::A));
		SetTeam(ETeamId::B, GameState->GetTeam(ETeamId::B));
	}

	FloatFormatOptions.MaximumFractionalDigits = 0;
	FloatFormatOptions.RoundingMode = ERoundingMode::HalfToZero;
}

void UMatchViewModel::SetTeam(const ETeamId TeamId, const FTeam& NewTeam)
{
	if (TeamId == ETeamId::A)
	{
		TeamA = NewTeam;
		if (TeamA != NewTeam)
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamAName);
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamAScore);
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamAColor);
		}
	}
	else
	{
		TeamB = NewTeam;
		if (TeamB != NewTeam)
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamBName);
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamBScore);
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamBColor);
		}
	}
}

void UMatchViewModel::SetTeamColor(const ETeamId TeamId, const FColor& NewColor)
{
	FTeam& Team = TeamId == ETeamId::A ? TeamA : TeamB;
	Team.Color = NewColor;

	if (TeamId == ETeamId::A)
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamAColor);
	}
	else
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamBColor);
	}
}

void UMatchViewModel::SetTeamName(const ETeamId TeamId, const FName& NewName)
{
	FTeam& Team = TeamId == ETeamId::A ? TeamA : TeamB;
	Team.Name = NewName;

	if (TeamId == ETeamId::A)
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamAName);
	}
	else
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamBName);
	}
}

void UMatchViewModel::SetTeamScore(const ETeamId TeamId, int32 NewScore)
{
	FTeam& Team = TeamId == ETeamId::A ? TeamA : TeamB;
	Team.Score = NewScore;

	if (TeamId == ETeamId::A)
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamAScore);
	}
	else
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetTeamBScore);
	}
}

void UMatchViewModel::SetMaxTeamScore(int32 NewMaxScore)
{
	MaxTeamScore = NewMaxScore;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxTeamScore);
}

void UMatchViewModel::SetMatchRemainingTime(float NewRemainingTime)
{
	MatchRemainingTime = NewRemainingTime;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMatchRemainingTime);
}

void UMatchViewModel::OnUpdateMatchTimer()
{
	if (GameMode)
	{
		const float RemainingTime = GameMode->GetRemainingMatchTime();
		if (RemainingTime >= 0.f) {
			SetMatchRemainingTime(RemainingTime);
		}
	}
}
