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
	BonusMesh->SetRelativeScale3D(FVector(0.4f));
	BonusMesh->BodyInstance.bAutoWeld = false;
	BonusMesh->BodyInstance.bGenerateWakeEvents = false;
	BonusMesh->bCastDynamicShadow = false;
	BonusMesh->bCastStaticShadow = false;
	BonusMesh->CastShadow = false;
	BonusMesh->SetCollisionProfileName(TEXT("NoCollision"));
	BonusMesh->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetRelativeScale3D(FVector(1.0f,2.0f,2.0f));
	Trigger->SetBoxExtent(FVector(64.0f, 128.0f, 32.0f));
	Trigger->SetCollisionProfileName(TEXT("Custom"));
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Ignore);
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

