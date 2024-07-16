// Fill out your copyright notice in the Description page of Project Settings.


#include "WinnerTeamController.h"
#include "GauntletModule.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogAutomation)

void UWinnerTeamController::OnInit()
{
	if (GetGauntlet())
	{
		GetGauntlet()->SetScreenshotPeriod(1.f);
	}
}

void UWinnerTeamController::OnPostMapChange(UWorld* World)
{
	UE_LOG(LogAutomation, Display, TEXT("Loaded map: %s"), *World->GetName());

	GameMode = Cast< ACTFGameMode>(UGameplayStatics::GetGameMode(World));

	if (GameMode)
	{
		GameMode->OnTeamScored(ExpectedWinner);
		GameMode->OnMatchEndDelegate.AddDynamic(this, &UWinnerTeamController::OnMatchEnd);
	}
	else
	{
		UE_LOG(LogAutomation, Error, TEXT("FAILURE: Unable to obtain GameMode reference"));
		EndTest(1);
	}
}

void UWinnerTeamController::OnMatchEnd(ETeamId TeamId)
{
	if (TeamId == ExpectedWinner)
	{
		UE_LOG(LogAutomation, Display, TEXT("SUCCESS: Expected team won the match"));
		EndTest(0);
	}
	else
	{
		UE_LOG(LogAutomation, Error, TEXT("FAILURE: Expected team %d to win but team %d was the winner"), ExpectedWinner, TeamId);
		EndTest(1);
	}
	
}
