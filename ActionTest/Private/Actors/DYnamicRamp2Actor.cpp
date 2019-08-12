// Fill out your copyright notice in the Description page of Project Settings.

#include "DYnamicRamp2Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"


ADYnamicRamp2Actor::ADYnamicRamp2Actor()
{
	PrimaryActorTick.bCanEverTick = true;

	Pirvot = CreateDefaultSubobject<UArrowComponent>(TEXT("Pirvot"));

	RootComponent = Pirvot;

	Box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box1"));

	Box1->SetRelativeLocation(FVector(934.0,85.0f,9.0f));
	Box1->SetRelativeScale3D(FVector(18.5f, 7.0f, 1.0f));
	Box1->SetBoxExtent(FVector(50.0f,32.0f,32.0f));
	Box1->BodyInstance.bNotifyRigidBodyCollision = true;
	Box1->SetCollisionProfileName(FName(TEXT("InvisibleWallDynamic")));
	Box1->SetupAttachment(RootComponent);

	Trigger->SetRelativeLocation(FVector(-156.0f, 0.0f, 226.0f));
	Trigger->SetRelativeScale3D(FVector(4.0f, 5.2f, 7.6f));
	Trigger->SetCollisionProfileName(FName(TEXT("Custom")));
	Trigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Trigger->SetupAttachment(RootComponent);

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	Explosion->SetAutoActivate(false);
	Explosion->SetupAttachment(RootComponent);

	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh1"));
	StaticMesh1->SetRelativeLocation(FVector(0.0f, 0.0f, 19.9f));
	StaticMesh1->BodyInstance.bAutoWeld = false;
	StaticMesh1->SetCollisionProfileName(FName(TEXT("NoCollision")));
	StaticMesh1->SetupAttachment(RootComponent);

	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh2"));
	StaticMesh2->SetRelativeLocation(FVector(508.6f, 0.0f, 19.9f));
	StaticMesh2->BodyInstance.bAutoWeld = false;
	StaticMesh2->SetCollisionProfileName(FName(TEXT("NoCollision")));
	StaticMesh2->SetupAttachment(RootComponent);

	StaticMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh3"));
	StaticMesh3->SetRelativeLocation(FVector(1019.4f, 0.0f, 19.9f));
	StaticMesh3->SetRelativeScale3D(FVector(1.6f, 1.0f, 1.0f));
	StaticMesh3->BodyInstance.bAutoWeld = false;
	StaticMesh3->SetCollisionProfileName(FName(TEXT("NoCollision")));
	StaticMesh3->SetupAttachment(RootComponent);

	StaticMesh4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh4"));
	StaticMesh4->SetRelativeLocation(FVector(0.0f, 323.3f, -15.0f));
	StaticMesh4->BodyInstance.bAutoWeld = false;
	StaticMesh4->SetCollisionProfileName(FName(TEXT("NoCollision")));
	StaticMesh4->SetupAttachment(RootComponent);
}


void ADYnamicRamp2Actor::BeginPlay()
{
	Super::BeginPlay();
	
}


void ADYnamicRamp2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

