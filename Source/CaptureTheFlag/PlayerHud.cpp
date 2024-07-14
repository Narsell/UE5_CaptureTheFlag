// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHud.h"
#include "CTFPlayerState.h"
#include "CTFGameMode.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h" 
#include "CaptureTheFlagCharacter.h"
#include "PlayerNotificationToast.h"
#include "PlayerOnlineDataHolder.h"


void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UPlayerHud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FWidgetAnimationDynamicEvent InToastAnimationFinishDelegate;
	InToastAnimationFinishDelegate.BindUFunction(this, FName("OnInToastAnimationFinished"));
	BindToAnimationFinished(InPlayerToastAnimation, InToastAnimationFinishDelegate);
} 

void UPlayerHud::OnFriendStatusNotification(UPlayerOnlineDataHolder* PlayerOnlineObject)
{
	if (PlayerOnlineObject)
	{
		PlayerNotificationToast->InitializeWithData(PlayerOnlineObject->GetData());
		PlayAnimation(InPlayerToastAnimation);
	}
}

void UPlayerHud::OnInToastAnimationFinished()
{
	FTimerHandle ToastHandle;
	GetWorld()->GetTimerManager().SetTimer(ToastHandle, FTimerDelegate::CreateLambda(
		[this] {
			PlayAnimation(OutPlayerToastAnimation);
		}
	), PlayerNotificationToast->GetDisplayTime(), false);
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

