// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFPlayerState.h"
#include "PlayerViewModel.h"
#include "CaptureTheFlagCharacter.h"
#include "HealthComponent.h"


void ACTFPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPlayerController())
	{
		return;
	}

	ACaptureTheFlagCharacter* PlayerCharacter = Cast<ACaptureTheFlagCharacter>(GetPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerHealthComponent = PlayerCharacter->GetHealthComponent();
	}


}

float ACTFPlayerState::GetCurrentHealth() const
{
	if (PlayerHealthComponent)
	{
		return PlayerHealthComponent->GetCurrentHealth();
	}
	return 0.f;
}

float ACTFPlayerState::GetMaxHealth() const
{
	if (PlayerHealthComponent)
	{
		return PlayerHealthComponent->GetMaxHealth();
	}
	return 0.f;
}
