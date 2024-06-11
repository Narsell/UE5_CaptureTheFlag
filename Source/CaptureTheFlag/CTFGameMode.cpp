// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFGameMode.h"
#include "Kismet/GameplayStatics.h" 
#include "TimerManager.h"

ACTFGameMode::ACTFGameMode()
	:
	GameState(nullptr)
{
}

void ACTFGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameState = Cast<ACTFGameState>(UGameplayStatics::GetGameState(this));

	GetWorldTimerManager().SetTimer(MatchTimerHandle, this, &ACTFGameMode::MatchTimerEnd, MatchTimeSeconds, false);
}

void ACTFGameMode::MatchTimerEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Match finished!"))

	const FTeam& TeamA = GameState->GetTeam(ETeamId::A);
	const FTeam& TeamB = GameState->GetTeam(ETeamId::B);

	const FTeam* WinnerTeam = nullptr;

	if (TeamA.Score != TeamB.Score) {
		WinnerTeam = &(TeamA.Score > TeamB.Score ? TeamA : TeamB);
	}
	else {

		if (!bHasExtraTimeHappened) {
			// Call delegate on UI to show extend timer function
			UE_LOG(LogTemp, Warning, TEXT("Tie. You have %f more seconds to sweep it!"), ExtraTimeSeconds)
			GetWorldTimerManager().SetTimer(MatchTimerHandle, this, &ACTFGameMode::MatchTimerEnd, ExtraTimeSeconds, false);
			bHasExtraTimeHappened = true;
			return;
		}
		else {
			// Determine winner by some other metric (most kills, most damage, etc...)
			WinnerTeam = &TeamA;
		}
	}

	// Call delegate on UI to popup winner msg or something
	ensure(WinnerTeam);
	UE_LOG(LogTemp, Warning, TEXT("Team %s won!"), *(WinnerTeam->Name.ToString()))

}

void ACTFGameMode::OnTeamScored(const ETeamId& TeamId)
{
	ensure(GameState);

	if (GameState && GetWorldTimerManager().IsTimerActive(MatchTimerHandle)) {
		GameState->AddScoreToTeam(TeamId);
		OnTeamScoreDelegate.ExecuteIfBound(TeamId);
		// If team scored while on extra time
		if (bHasExtraTimeHappened) {
			const FTeam& WinnerTeam = GameState->GetTeam(TeamId);
			GetWorldTimerManager().ClearTimer(MatchTimerHandle);
			UE_LOG(LogTemp, Warning, TEXT("Team %s won!"), *(WinnerTeam.Name.ToString()))
		}
	}
}

