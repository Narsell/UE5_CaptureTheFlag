// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHud.h"
#include "CTFPlayerState.h"
#include "CTFGameMode.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h" 


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	// Setting references
	PlayerState = Cast<ACTFPlayerState>(GetOwningPlayerState());
	GameState = Cast<ACTFGameState>(UGameplayStatics::GetGameState(this));
	GameMode = Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(this));

	if (!PlayerState || !GameState || !GameMode) return;
	ensure(PlayerState && GameState && GameMode);

	// Binding delegates to update functions.
	PlayerState->OnCurrentHealthUpdateDelegate.BindUObject(this, &UPlayerHud::UpdateCurrentHealth);
	PlayerState->OnMaxHealthUpdateDelegate.BindUObject(this, &UPlayerHud::UpdateMaxHealth);
	GameMode->OnTeamScoreDelegate.BindUObject(this, &UPlayerHud::UpdateTeamScore);
	
	// Some formatting options to display floats as integers
	HealthFormatOptions.SetMaximumFractionalDigits(0);

	// Update elements with current values when the widget is created.
	UpdateCurrentHealth(PlayerState->GetCurrentHealth());
	UpdateMaxHealth(PlayerState->GetMaxHealth());
	UpdateTeamNames();
	UpdateTeamMaxScores();
	UpdateTeamScore(ETeamId::A);
	UpdateTeamScore(ETeamId::B);
	
}

void UPlayerHud::UpdateCurrentHealth(float NewHealth)
{
	CurrentHealthLabel->SetText(FText::AsNumber(NewHealth, &HealthFormatOptions));
	HealthBar->SetPercent(NewHealth / PlayerState->GetMaxHealth());
}

void UPlayerHud::UpdateMaxHealth(float NewMaxHealth) 
{
	MaxHealthLabel->SetText(FText::AsNumber(NewMaxHealth, &HealthFormatOptions));
	HealthBar->SetPercent(PlayerState->GetCurrentHealth() / NewMaxHealth);
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
