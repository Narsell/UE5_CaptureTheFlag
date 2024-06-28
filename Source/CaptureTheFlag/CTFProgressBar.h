// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTFProgressBar.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UCTFProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Binding)
	void SetPercent(float InPercent);

	UFUNCTION(BlueprintCallable, Category = Binding)
	void SetCurrentValue(const FText& InCurrentValue);

	UFUNCTION(BlueprintCallable, Category = Binding)
	void SetMaxValue(const FText& InCurrentValue);

protected:

	virtual void NativePreConstruct() override;
	
protected:
	
	UPROPERTY(EditInstanceOnly, Category = Setup)
	FLinearColor FillColor = FLinearColor::Green;

	/* BIND WIDGETS VARIABLES */

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxLabel;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;
	
};
