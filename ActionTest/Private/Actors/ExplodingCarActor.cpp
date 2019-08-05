// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplodingCarActor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"


AExplodingCarActor::AExplodingCarActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMeshCar (TEXT("StaticMesh'/Game/Environment/Car_Cabriolet_01.Car_Cabriolet_01'"));

	ConstructorHelpers::FObjectFinder<UMaterialInstance>
		StaticMaterialCar(TEXT("MaterialInstanceConstant'/Game/Environment/materials/M_Car_Cabriolet_05.M_Car_Cabriolet_05'"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	if (StaticMeshCar.Object != NULL)
	{
		Mesh->SetStaticMesh(StaticMeshCar.Object);
	}

	if (StaticMaterialCar.Object != NULL)
	{
		TArray<FName> MaterialNames=Mesh->GetMaterialSlotNames();
		Mesh->SetMaterialByName(MaterialNames[0], StaticMaterialCar.Object);
	}

	
	Box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box1"));
	Box1->SetRelativeLocation(FVector(0.0f,0.0f,79.510361f));
	Box1->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));
	Box1->SetBoxExtent(FVector(120.0f, 96.0f, 64.0f));
	Box1->SetGenerateOverlapEvents(false);
	Box1->SetCollisionProfileName(FName(TEXT("Custom")));
	Box1->SetCollisionResponseToAllChannels(ECR_Block);

	Colission = CreateDefaultSubobject<UBoxComponent>(TEXT("Colission"));
	Colission->SetRelativeLocation(FVector(-5.940163f, 0.0, 98.395767));
	Colission->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));
	Colission->SetBoxExtent(FVector(128.0f,96.0f,64.0f));
	Colission->SetCollisionProfileName(FName(TEXT("OverlapOnlyPawn")));

	CloseContactTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CloseContactTrigger"));
	CloseContactTrigger->SetRelativeLocation(FVector(-214.00456, 0.0, 82.048523));
	CloseContactTrigger->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));
	CloseContactTrigger->SetBoxExtent(FVector(32.0f, 96.0f, 48.0f));
	CloseContactTrigger->SetCollisionProfileName(FName(TEXT("OverlapAllDynamic")));

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));

	Mask = CreateDefaultSubobject<UStaticMeshComponent>("Mask");

	RoofBack = CreateDefaultSubobject<UStaticMeshComponent>("RoofBack");

	RoofTop = CreateDefaultSubobject<UStaticMeshComponent>("RoofTop");

	RootComponent = Mesh;

	Box1->SetupAttachment(RootComponent);

	Colission->SetupAttachment(RootComponent);

	CloseContactTrigger->SetupAttachment(RootComponent);

	Explosion->SetupAttachment(RootComponent);

	Mask->SetupAttachment(RootComponent);

	RoofBack->SetupAttachment(RootComponent);

	RoofTop->SetupAttachment(RootComponent);
}


void AExplodingCarActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplodingCarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

