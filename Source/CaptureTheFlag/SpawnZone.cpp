// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnZone.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/ArrowComponent.h" 
#include "TeamBase.h"

ASpawnZone::ASpawnZone()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITOR

	CreateEditorOnlyComponents();

#endif

}

void ASpawnZone::SetOwnerBase(ATeamBase* TeamBase)
{
	OwnerBase = TeamBase;
}

void ASpawnZone::BeginPlay()
{
	Super::BeginPlay();

	if (!SpawnClass.Get()) return; 

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AActor* SpawnedActor = GetWorld()->SpawnActor(SpawnClass.Get(), &GetTransform(), SpawnParams);

}

#if WITH_EDITOR

void ASpawnZone::UpdateEditorValues()
{
	if (EditorCustomName.Len() > 0) {
		EditorTextRenderName->SetText(FText::FromString(EditorCustomName));
	}
	else {
		EditorTextRenderName->SetText(FText::FromString(SpawnClass.Get() ? SpawnClass.Get()->GetName() : EditorCustomName));
	}

	if (OwnerBase && !OwnerBase->GetSpawnZones().Contains(this)) {
		OwnerBase = nullptr;
	}
}

void ASpawnZone::CreateEditorOnlyComponents()
{
	EditorLocationSprite = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("LocationSprite"));
	EditorTextRenderName = CreateEditorOnlyDefaultSubobject<UTextRenderComponent>(TEXT("DisplayName"));
	EditorForwardArrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));

	if (EditorLocationSprite)
	{
		EditorLocationSprite->bHiddenInGame = true;
		SetRootComponent(EditorLocationSprite);
	}
	if (EditorTextRenderName)
	{
		EditorTextRenderName->SetupAttachment(RootComponent);
		EditorTextRenderName->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		EditorTextRenderName->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
		EditorTextRenderName->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
		EditorTextRenderName->SetWorldSize(20.f);
		EditorTextRenderName->bHiddenInGame = true;
	}
	if (EditorForwardArrow)
	{
		EditorForwardArrow->SetupAttachment(RootComponent);
		EditorForwardArrow->ArrowColor = FColor(149, 199, 254);
	}
}

#endif
