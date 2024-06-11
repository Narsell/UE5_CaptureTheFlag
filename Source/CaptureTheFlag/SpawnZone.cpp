// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnZone.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/ArrowComponent.h" 

ASpawnZone::ASpawnZone()
{
	PrimaryActorTick.bCanEverTick = false;

	EditorLocationSprite = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("LocationSprite"));
	EditorTextRenderName = CreateEditorOnlyDefaultSubobject<UTextRenderComponent>(TEXT("DisplayName"));
	EditorForwardArrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));

	EditorLocationSprite->bHiddenInGame = true;
	SetRootComponent(EditorLocationSprite);

	EditorTextRenderName->SetupAttachment(RootComponent);
	EditorTextRenderName->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	EditorTextRenderName->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	EditorTextRenderName->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	EditorTextRenderName->SetWorldSize(20.f);
	EditorTextRenderName->bHiddenInGame = true;

	EditorForwardArrow->SetupAttachment(RootComponent);
	EditorForwardArrow->ArrowColor = FColor(149, 199, 254);

}

void ASpawnZone::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnClass.Get()) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		GetWorld()->SpawnActor(SpawnClass.Get(), &GetTransform(), SpawnParams);
	}

}

void ASpawnZone::SetEditorDisplayName()
{
	if (EditorCustomName.Len() > 0) {
		EditorTextRenderName->SetText(FText::FromString(EditorCustomName));
	}
	else {
		EditorTextRenderName->SetText(FText::FromString(SpawnClass.Get() ? SpawnClass.Get()->GetName() : EditorCustomName));
	}
}

