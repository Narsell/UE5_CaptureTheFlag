// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHud.h"
#include "CTFPlayerState.h"
#include "CTFGameMode.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h" 
#include "CaptureTheFlagCharacter.h"


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UPlayerHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UPlayerHud::UpdateTeamNames()
{
	if (!GameState) return;

	const FTeam TeamA = GameState->GetTeam(ETeamId::A);
	const FTeam TeamB = GameState->GetTeam(ETeamId::B);

	TeamANameLabel->SetText(FText::FromName(TeamA.Name));
	TeamANameLabel->SetColorAndOpacity(FSlateColor(TeamA.Color));

	TeamBNameLabel->SetText(FText::FromName(TeamB.Name));
	TeamBNameLabel->SetColorAndOpacity(FSlateColor(TeamB.Color));
}

void UPlayerHud::UpdateTeamScore(const ETeamId& TeamId)
{
	if (!GameState) return;

	UTextBlock* ScoreLabel = TeamId == ETeamId::A ? TeamAScoreLabel : TeamBScoreLabel;
	int32 NewScore = GameState->GetTeam(TeamId).Score;
	ScoreLabel->SetText(FText::AsNumber(NewScore));
}

void UPlayerHud::UpdateTeamMaxScores()
{
	if (!GameMode) return;

	const int32 ScoreToWin = GameMode->GetRequiredScoreToWin();

	TeamAMaxScoreLabel->SetText(FText::AsNumber(ScoreToWin));
	TeamBMaxScoreLabel->SetText(FText::AsNumber(ScoreToWin));
}
