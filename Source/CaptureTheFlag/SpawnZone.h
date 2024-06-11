// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnZone.generated.h"

class UTextRenderComponent;
class UArrowComponent;


UCLASS(Abstract)
class CAPTURETHEFLAG_API ASpawnZone : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnZone();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetEditorDisplayName();

private:

	UPROPERTY(EditAnywhere, Category=Setup)
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY(EditDefaultsOnly, Category=Visibility)
	UBillboardComponent* EditorLocationSprite;

	UPROPERTY(EditDefaultsOnly, Category=Visibility)
	UTextRenderComponent* EditorDisplayName;

	UPROPERTY(EditDefaultsOnly, Category=Visibility)
	UArrowComponent* EditorForwardArrow;

};
