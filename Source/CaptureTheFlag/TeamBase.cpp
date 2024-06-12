// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamBase.h"
#include "Components/ShapeComponent.h"
#include "Components/BillboardComponent.h" 
#include "Flag.h"
#include "Kismet/GameplayStatics.h" 
#include "CaptureTheFlagCharacter.h"
#include "CTFGameMode.h"

ATeamBase::ATeamBase()
	:
	DropFlagSocket(CreateDefaultSubobject<USceneComponent>(TEXT("FlagSocket"))),
	TeamId(ETeamId::A),
	GameMode(nullptr)
{
	SetActorHiddenInGame(false);

	GetCollisionComponent()->bHiddenInGame = true;
	GetCollisionComponent()->SetCollisionObjectType(ECC_Base);
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATeamBase::OnFlagEntered);

	DropFlagSocket->SetupAttachment(RootComponent);

}

void ATeamBase::BeginPlay()
{
	GetSpriteComponent()->SetVisibility(false);
	GameMode = Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(this));

}

void ATeamBase::ResizeSpawnZones()
{

}

// TODO: Detect player entering instead, check collision profiles. Team base should overlap pawn only, pawn should overlap team base as well.
void ATeamBase::OnFlagEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AFlag* Flag = Cast<AFlag>(OtherActor);

	ensure(Flag);

	if (Flag && Flag->GetCarrier()) {
		Flag->GetCarrier()->DropFlag();
		Flag->SetActorLocation(DropFlagSocket->GetComponentLocation());
		ensure(GameMode);
		if (GameMode) {
			GameMode->OnTeamScored(TeamId);
		}
	}
}
