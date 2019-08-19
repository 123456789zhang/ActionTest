// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeBonusActor.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATimeBonusActor::ATimeBonusActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = Arrow;

	TextPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TextPlane"));
	TextPlane->SetRelativeTransform(FTransform(FRotator(0.0f,269.9f,0.0f), FVector(0.42f,253.83f,109.5f), FVector(1.0f,1.0f,0.7f)));
	TextPlane->BodyInstance.bAutoWeld = false;
	TextPlane->BodyInstance.bGenerateWakeEvents = false;
	TextPlane->SetCollisionProfileName(TEXT("NoCollision"));
	TextPlane->bCastDynamicShadow = false;
	TextPlane->bCastStaticShadow = false;
	TextPlane->CastShadow = false;
	TextPlane->SetupAttachment(RootComponent);

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));

	BonusMesh->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	Trigger->SetupAttachment(RootComponent);

	Fx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fx"));

	Fx->SetupAttachment(RootComponent);
}

void ATimeBonusActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATimeBonusActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

