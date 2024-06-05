// Fill out your copyright notice in the Description page of Project Settings.


#include "Flag.h"
#include "Components/ShapeComponent.h"
#include "CaptureTheFlagCharacter.h"
#include "Components/BillboardComponent.h" 

AFlag::AFlag()
{
	PoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pole Mesh"));
	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flag Mesh"));

	PoleMesh->SetupAttachment(RootComponent);
	FlagMesh->SetupAttachment(RootComponent);

	PoleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FlagMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetActorHiddenInGame(false);

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFlag::OnGrabbed);
}

void AFlag::BeginPlay()
{
	Super::BeginPlay();
	GetSpriteComponent()->SetVisibility(false);

}

void AFlag::OnGrabbed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACaptureTheFlagCharacter* Player = Cast<ACaptureTheFlagCharacter>(OtherActor);
	if (Player) {
		Player->GrabFlag(this);
	}
}
