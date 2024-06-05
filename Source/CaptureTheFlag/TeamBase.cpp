// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamBase.h"
#include "Components/ShapeComponent.h"
#include "Components/BillboardComponent.h" 


ATeamBase::ATeamBase()
{
	SetActorHiddenInGame(false);

	GetCollisionComponent()->bHiddenInGame = true;
	GetCollisionComponent()->SetCollisionObjectType(ECC_Base);
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATeamBase::OnFlagEntered);
}

void ATeamBase::BeginPlay()
{
	GetSpriteComponent()->SetVisibility(false);

}

void ATeamBase::OnFlagEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("POINT TO TEAM [PLACEHOLDER]"))
}
