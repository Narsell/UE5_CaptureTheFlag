// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamBase.h"
#include "Components/ShapeComponent.h"
#include "Components/BillboardComponent.h" 
#include "Flag.h"
#include "Kismet/GameplayStatics.h" 
#include "CaptureTheFlagCharacter.h"
#include "CTFGameMode.h"
#include "SpawnZone.h"

ATeamBase::ATeamBase()
	:
	DropFlagSocket(CreateDefaultSubobject<USceneComponent>(TEXT("FlagSocket")))
{
	SetActorHiddenInGame(false);

	GetCollisionComponent()->bHiddenInGame = true;
	GetCollisionComponent()->SetCollisionObjectType(ECC_Base);
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATeamBase::OnFlagEntered);

	DropFlagSocket->SetupAttachment(RootComponent);

	SpawnZones.Reserve(3);
}

void ATeamBase::BeginPlay()
{
#if WITH_EDITOR
	GetSpriteComponent()->SetVisibility(false);
#endif

	GameMode = Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(this));

}

void ATeamBase::SetupSpawnZones()
{
	for (int i = 0; i < SpawnZones.Num(); ++i)
	{
		if (!SpawnZones[i]) continue;
		else if (SpawnZones[i]->GetTeamBase() && SpawnZones[i]->GetTeamBase() != this && SpawnZones[i]->GetTeamBase()->SpawnZones.Contains(SpawnZones[i]))
		{
			SpawnZones[i]->GetTeamBase()->SpawnZones.Remove(SpawnZones[i]);
		}
		SpawnZones[i]->SetOwnerBase(this);
	}
}

void ATeamBase::OnFlagEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ACaptureTheFlagCharacter* Player = Cast<ACaptureTheFlagCharacter>(OtherActor);

	if (!Player) return;

	AFlag* Flag = Player->GetCarryingFlag();

	if (Flag && Flag->GetTeamId() != TeamId) {
		Player->DropFlag();
		Flag->SetActorLocation(DropFlagSocket->GetComponentLocation());
		ensure(GameMode);
		if (GameMode) {
			GameMode->OnTeamScored(TeamId);
		}
	}
}
