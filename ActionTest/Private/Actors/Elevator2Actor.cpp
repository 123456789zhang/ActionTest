// Fill out your copyright notice in the Description page of Project Settings.

#include "Elevator2Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"


AElevator2Actor::AElevator2Actor()
{
	static ConstructorHelpers::FObjectFinder<UMaterial>
		StaticMeshMaterial(TEXT("Material'/Game/Environment/M_Metal_01_TEMP.M_Metal_01_TEMP'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMeshOne(TEXT("StaticMesh'/Game/Environment/Elevator_short.Elevator_short'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMeshTwo(TEXT("StaticMesh'/Game/Environment/meshes/EditorCube.EditorCube'"));

	GetMesh()->SetRelativeLocation(FVector(-30.0f, 0.0f, 37.0f));
	GetMesh()->CastShadow = false;
	GetMesh()->bAffectDynamicIndirectLighting = false;
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->bCastStaticShadow = false;
	GetMesh()->bHiddenInGame = true;
	GetMesh()->SetMaterial(0, StaticMeshMaterial.Object);

	Elev = CreateDefaultSubobject<UArrowComponent>(TEXT("Elev"));
	Elev->SetRelativeLocation(FVector(404.33f,1.2f,-105.7f));

	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh1"));
	StaticMesh1->SetRelativeLocation(FVector(3450.0f,0.0f,300.61f));
	StaticMesh1->SetRelativeScale3D(FVector(4.0f, 1.0f, 4.0f));
	StaticMesh1->BodyInstance.bAutoWeld = false;
	StaticMesh1->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMesh1->CastShadow = false;
	StaticMesh1->SetStaticMesh(StaticMeshOne.Object);
	StaticMesh1->SetupAttachment(Elev);

	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh2"));
	StaticMesh2->SetRelativeLocation(FVector(-462.5f, 0.0f, -2.43f));
	StaticMesh2->SetRelativeScale3D(FVector(4.5f, 1.0f, 0.03f));
	StaticMesh2->BodyInstance.bAutoWeld = false;
	StaticMesh2->SetCollisionProfileName(TEXT("BlockAll"));
	StaticMesh2->CastShadow = false;
	StaticMesh2->SetHiddenInGame(true);
	StaticMesh2->SetStaticMesh(StaticMeshTwo.Object);
	StaticMesh2->SetupAttachment(StaticMesh1);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetRelativeTransform(FTransform(FRotator(0.0f), FVector(-4096.0f, 0.0f, 0.0f), FVector(4.0f, 1.0f, 8.0f)));
	Trigger->SetBoxExtent(FVector(128.0f, 128.0f, 1024.0f));
	Trigger->bAlwaysCreatePhysicsState = true;
	FComponentBeginOverlapSignature BeginOverlap;
	BeginOverlap.__Internal_AddDynamic(this, &AElevator2Actor::TriggerBeginOverlap, FName(TEXT("TriggerBeginOverlap")));
	Trigger->OnComponentBeginOverlap = BeginOverlap;
	Trigger->SetupAttachment(Elev);

	SoundStop = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundStop"));
	SoundStop->SetRelativeLocation(FVector(-231.96f,0.0f, 290.72f));
	SoundStop->AttenuationOverrides.FalloffDistance = 3000.0f;
	SoundStop->SetVolumeMultiplier(0.2f);
	SoundStop->PitchMultiplier = 0.8f;
	SoundStop->bAutoActivate = false;
	SoundStop->AttenuationOverrides.bAttenuateWithLPF = false;
	SoundStop->AttenuationOverrides.LPFRadiusMin = 2000.0f;
	SoundStop->AttenuationOverrides.LPFRadiusMax = 3000.0f;
	SoundStop->SetupAttachment(Elev);

	SoundStart = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundStart"));
	SoundStart->SetRelativeLocation(FVector(-168.72f, 0.0f, 345.2f));
	SoundStart->AttenuationOverrides.FalloffDistance = 3000.0f;
	SoundStart->SetVolumeMultiplier(0.2f);
	SoundStart->PitchMultiplier = 0.8f;
	SoundStart->bAutoActivate = false;
	SoundStart->AttenuationOverrides.bAttenuateWithLPF = false;
	SoundStart->AttenuationOverrides.LPFRadiusMin = 2000.0f;
	SoundStart->AttenuationOverrides.LPFRadiusMax = 3000.0f;
	SoundStart->SetupAttachment(Elev);
}

void AElevator2Actor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	//low_position = GetMesh()->GetComponentLocation().Z;

	//Trigger->AddRelativeLocation(FVector(TriggerOffset, 0.0f, 0.0f));

	Elev->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	bTempOnce = false;
}

void AElevator2Actor::BeginPlay()
{
	Super::BeginPlay();


}

void AElevator2Actor::TriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bTempOnce)
	{

	}
}
