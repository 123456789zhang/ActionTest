// Fill out your copyright notice in the Description page of Project Settings.

#include "TextActor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Engine.h"


ATextActor::ATextActor()
{
	Object = CreateDefaultSubobject<UArrowComponent>(TEXT("Object"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

	Trigger->SetRelativeLocation(FVector(0.0f,320.0f,2.732391f));
	Trigger->SetBoxExtent(FVector(512.0f, 32.0f, 768.0f));
	Trigger->OnComponentBeginOverlap.__Internal_AddDynamic(this, &ATextActor::OnComponentBeginOverlap,FName(TEXT("OnComponentBeginOverlap")));

	Text->SetRelativeLocation(FVector(0.0f, -512.0f, 0.0f));
	Text->SetRelativeScale3D(FVector(4.0f));
	Text->VerticalAlignment = EVerticalTextAligment::EVRTA_QuadTop;
	Text->bHiddenInGame = true;

	RootComponent = Object;

	Trigger->SetupAttachment(RootComponent);
	Text->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;

}


void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATextActor::BeginPlay()
{
	Super::BeginPlay();

}

void ATextActor::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Yellow,*FString(TEXT("开始触碰")));
}

