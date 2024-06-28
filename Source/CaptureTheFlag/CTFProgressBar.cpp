// Fill out your copyright notice in the Description page of Project Settings.


#include "CTFProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UCTFProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	ProgressBar->SetFillColorAndOpacity(FillColor);
}

void UCTFProgressBar::SetPercent(float InPercent)
{
	ProgressBar->SetPercent(InPercent);
}

void UCTFProgressBar::SetCurrentValue(const FText& InCurrentValue)
{
	CurrentLabel->SetText(InCurrentValue);
}

void UCTFProgressBar::SetMaxValue(const FText& InCurrentValue)
{
	MaxLabel->SetText(InCurrentValue);
}

