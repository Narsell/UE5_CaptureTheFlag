// Fill out your copyright notice in the Description page of Project Settings.


#include "Flag.h"
#include "Components/ShapeComponent.h"
#include "CaptureTheFlagCharacter.h"
#include "Components/BillboardComponent.h" 

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

	//ensure(Player);

	if (Player) {
		Player->GrabFlag(this);
		Carrier = Player;
		GetCollisionComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	}
}
