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

	// Setting references
	PlayerCharacter = GetOwningPlayerPawn<ACaptureTheFlagCharacter>();
	PlayerState = Cast<ACTFPlayerState>(GetOwningPlayerState());
	GameState = Cast<ACTFGameState>(UGameplayStatics::GetGameState(this));
	GameMode = Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(this));

	ensure(PlayerState && GameState && GameMode && PlayerCharacter);
	if (!PlayerState || !GameState || !GameMode ||!PlayerCharacter) return;

	// Binding delegates to update functions.
	PlayerState->OnCurrentHealthUpdateDelegate.BindUObject(this, &UPlayerHud::UpdateCurrentHealth);
	PlayerState->OnMaxHealthUpdateDelegate.BindUObject(this, &UPlayerHud::UpdateMaxHealth);
	PlayerCharacter->CurrentStaminaUpdateDelegate.BindUObject(this, &UPlayerHud::UpdateCurrentStamina);
	PlayerCharacter->MaxStaminaUpdateDelegate.BindUObject(this, &UPlayerHud::UpdateMaxStamina);
	GameMode->OnTeamScoreDelegate.BindUObject(this, &UPlayerHud::UpdateTeamScore);
	
	// Some formatting options to display floats as integers
	FloatFormatOptions.SetMaximumFractionalDigits(0);

	// Update elements with current values when the widget is created.
	CurrentHealth = PlayerState->GetCurrentHealth();
	MaxHealth = PlayerState->GetMaxHealth();
	UpdateCurrentHealth(CurrentHealth);
	UpdateMaxHealth(MaxHealth);

	CurrentStamina = PlayerCharacter->GetCurrentStamina();
	MaxStamina = PlayerCharacter->GetMaxStamina();
	UpdateCurrentStamina(CurrentStamina);
	UpdateMaxStamina(MaxStamina);

	UpdateTeamNames();
	UpdateTeamMaxScores();
	UpdateTeamScore(ETeamId::A);
	UpdateTeamScore(ETeamId::B);
	
}

void UPlayerHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetWorld()->GetTimerManager().IsTimerActive(GameMode->GetMatchTimerHandle())) {
		const float TimeLeftInMatch = GetWorld()->GetTimerManager().GetTimerRemaining(GameMode->GetMatchTimerHandle());
		MatchTimerLabel->SetText(FText::AsNumber(TimeLeftInMatch, &FloatFormatOptions));
	}
}

void UPlayerHud::UpdateCurrentHealth(float NewHealth)
{
	CurrentHealth = NewHealth;

	CurrentHealthLabel->SetText(FText::AsNumber(CurrentHealth, &FloatFormatOptions));
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}

void UPlayerHud::UpdateMaxHealth(float NewMaxHealth) 
{
	MaxHealth = NewMaxHealth;

	MaxHealthLabel->SetText(FText::AsNumber(MaxHealth, &FloatFormatOptions));
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}

void UPlayerHud::UpdateCurrentStamina(float NewStamina)
{
	CurrentStamina = NewStamina;

	CurrentStaminaLabel->SetText(FText::AsNumber(CurrentStamina, &FloatFormatOptions));
	StaminaBar->SetPercent(CurrentStamina / MaxStamina);
}

void UPlayerHud::UpdateMaxStamina(float NewMaxStamina)
{
	MaxStamina = NewMaxStamina;

	MaxStaminaLabel->SetText(FText::AsNumber(MaxStamina, &FloatFormatOptions));
	StaminaBar->SetPercent(CurrentStamina / MaxStamina);
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
