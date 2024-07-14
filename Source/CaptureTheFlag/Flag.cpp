// Fill out your copyright notice in the Description page of Project Settings.


#include "Flag.h"
#include "Components/ShapeComponent.h"
#include "CaptureTheFlagCharacter.h"
#include "Components/BillboardComponent.h" 
#include "CTFPlayerState.h"
#include "TeamBase.h"
#include "SpawnZone.h"

AFlag::AFlag()
	:
	PoleMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pole Mesh"))),
	FlagMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag Mesh")))
{

	PoleMesh->SetupAttachment(RootComponent);
	FlagMesh->SetupAttachment(RootComponent);

	PoleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FlagMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetActorHiddenInGame(false);

	GetCollisionComponent()->bHiddenInGame = true;
	GetCollisionComponent()->SetCollisionObjectType(ECC_Flag);


}

ACaptureTheFlagCharacter* AFlag::GetCarrier() const
{
	return Carrier.IsValid() ? Carrier.Get() : nullptr;
}

void AFlag::SetCarrier(ACaptureTheFlagCharacter* InCarrier)
{
	Carrier = InCarrier;
	GetCollisionComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void AFlag::Drop()
{
	Carrier.Reset();
	GetWorldTimerManager().SetTimer(DestructionTimer, this, &AFlag::GetDestroyed, TimeBeforeDestruction, false);
}

void AFlag::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	GetSpriteComponent()->SetVisibility(false);
#endif

	SetTeamColors();
}

void AFlag::GetDestroyed()
{
	Destroy();
}

void AFlag::SetTeamColors()
{
	ASpawnZone* SpawnZone = Cast<ASpawnZone>(GetOwner());

	if (SpawnZone && SpawnZone->GetTeamBase()) {
		TeamId = SpawnZone->GetTeamBase()->GetTeamId();
		SetTeamColorsEvent(TeamId);
	}
}
