// Fill out your copyright notice in the Description page of Project Settings.


#include "Flag.h"
#include "Components/ShapeComponent.h"
#include "CaptureTheFlagCharacter.h"
#include "Components/BillboardComponent.h" 
#include "CTFPlayerState.h"

AFlag::AFlag()
	:
	PoleMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pole Mesh"))),
	FlagMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag Mesh"))),
	Carrier(nullptr)
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

void AFlag::OnDropped()
{
	Carrier.Reset();
	GetWorldTimerManager().SetTimer(DestructionTimer, this, &AFlag::GetDestroyed, TimeBeforeDestruction, false);
}

void AFlag::BeginPlay()
{
	Super::BeginPlay();
	GetSpriteComponent()->SetVisibility(false);

}

void AFlag::GetDestroyed()
{
	Destroy();
}
