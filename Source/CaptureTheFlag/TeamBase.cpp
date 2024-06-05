// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamBase.h"
#include "Components/ShapeComponent.h"
#include "Components/BillboardComponent.h" 


ATeamBase::ATeamBase()
{
	SetActorHiddenInGame(false);

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATeamBase::OnFlagDrop);
}

void ATeamBase::BeginPlay()
{
	GetSpriteComponent()->SetVisibility(false);

}

void ATeamBase::OnFlagDrop(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
