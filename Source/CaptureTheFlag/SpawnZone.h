// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnZone.generated.h"

class UTextRenderComponent;
class UArrowComponent;
class ATeamBase;



UCLASS(Abstract)
class CAPTURETHEFLAG_API ASpawnZone : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnZone();

	/** Sets the reference to a new team base. */
	virtual void SetOwnerBase(ATeamBase* TeamBase);

	/** Returns the team base that owns this spawner, if any. */
	ATeamBase* GetTeamBase() const { return OwnerBase; }

protected:

	virtual void BeginPlay() override;

	/**
	 * Updates multiple variables relevant to be displayed while in-editor, useful for designers.
	 * Variables updated: Actor class/custom editor name to render, Team base owner reference.
	 */
	UFUNCTION(BlueprintCallable)
	void UpdateEditorValues();

private:

	/** Object reference to the team base that owns this spawner */
	UPROPERTY(VisibleInstanceOnly, Category=Setup)
	ATeamBase* OwnerBase;

	/** Class of the AActor that should spawn here */
	UPROPERTY(EditAnywhere, Category=Setup)
	TSubclassOf<AActor> SpawnClass;

	/** A sprite used to get in-editor visibility on the spawn point */
	UPROPERTY(EditDefaultsOnly, Category=Visibility)
	UBillboardComponent* EditorLocationSprite;

	/** A text render component to display the name of the object in-editor */
	UPROPERTY(EditDefaultsOnly, Category=Visibility)
	UTextRenderComponent* EditorTextRenderName;

	/** 
	 * An optional custom name to display in editor, leave empty to display 
	 * the class name set to spawn.
	 */
	UPROPERTY(EditInstanceOnly, Category=Setup)
	FString EditorCustomName = "";

	/** Arrow ponting to the direction the actor will spawn in. (Forward vector) */
	UPROPERTY(EditDefaultsOnly, Category=Visibility)
	UArrowComponent* EditorForwardArrow;

};
