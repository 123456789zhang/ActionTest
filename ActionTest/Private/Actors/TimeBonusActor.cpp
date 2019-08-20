// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeBonusActor.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Particles/ParticleSystem.h"

ATimeBonusActor::ATimeBonusActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticTextPlaneMesh(TEXT("StaticMesh'/Engine/EditorMeshes/EditorPlane.EditorPlane'"));

	static ConstructorHelpers::FObjectFinder<UMaterial>
		StaticTextPlaneMaterial(TEXT("Material'/Game/Environment/Time_Bonus_Mat.Time_Bonus_Mat'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticBonusMeshMesh(TEXT("StaticMesh'/Game/Environment/meshes/SM_PG_Time_Token.SM_PG_Time_Token'"));

	static  ConstructorHelpers::FObjectFinder<UMaterial>
		StaticBonusMeshMaterial(TEXT("Material'/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03'"));

	static  ConstructorHelpers::FObjectFinder<UParticleSystem>
		StaticFxParticleSystem(TEXT("ParticleSystem'/Game/Environment/particles/P_robot_electric_hand_02.P_robot_electric_hand_02'"));

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
	TextPlane->SetStaticMesh(StaticTextPlaneMesh.Object);
	TextPlane->GetStaticMesh()->SetMaterial(0, StaticTextPlaneMaterial.Object);
	TextPlane->SetupAttachment(RootComponent);

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));
	BonusMesh->SetRelativeScale3D(FVector(0.4f));
	BonusMesh->BodyInstance.bAutoWeld = false;
	BonusMesh->BodyInstance.bGenerateWakeEvents = false;
	BonusMesh->SetCollisionProfileName(TEXT("NoCollision"));
	BonusMesh->bCastDynamicShadow = false;
	BonusMesh->bCastStaticShadow = false;
	BonusMesh->CastShadow = false;
	BonusMesh->SetStaticMesh(StaticBonusMeshMesh.Object);
	BonusMesh->GetStaticMesh()->SetMaterial(0, StaticBonusMeshMaterial.Object);
	BonusMesh->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetRelativeScale3D(FVector(1.0f, 2.0f, 2.0f));
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
	Fx->SetRelativeScale3D(FVector(2.0f));
	Fx->SetTemplate(StaticFxParticleSystem.Object);
	Fx->SetupAttachment(RootComponent);
}

void ATimeBonusActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_BounMeshRotator, this, &ATimeBonusActor::BounMeshRotator, 0.05f, true);
}

void ATimeBonusActor::BounMeshRotator()
{
	FRotator OldRotator = BonusMesh->GetComponentRotation();

	FRotator NewRotator(OldRotator.Pitch, OldRotator.Yaw + 100, OldRotator.Roll);

	BonusMesh->SetWorldRotation(FMath::RInterpTo(OldRotator, NewRotator, 1.0f, 1.0f));
}

void ATimeBonusActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimeBonusActor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	TextPlane->SetVisibility(false);

	TextPlaneLocation = TextPlane->GetComponentLocation();

	TextPlaneScale = TextPlane->RelativeScale3D;
}

