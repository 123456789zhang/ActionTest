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
#include "ActionTestBlueprintLibrary.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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
	TextPlane->SetRelativeTransform(FTransform(FRotator(0.0f, 269.9f, 0.0f), FVector(0.42f, 253.83f, 109.5f), FVector(1.0f, 1.0f, 0.7f)));
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
	FComponentBeginOverlapSignature BeginOverlap;
	BeginOverlap.__Internal_AddDynamic(this, &ATimeBonusActor::TiggerComponentBeginOverlap, FName(TEXT("TiggerComponentBeginOverlap")));
	Trigger->OnComponentBeginOverlap = BeginOverlap;
	Trigger->SetupAttachment(RootComponent);

	Fx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fx"));
	Fx->SetRelativeScale3D(FVector(2.0f));
	Fx->SetTemplate(StaticFxParticleSystem.Object);
	Fx->SetupAttachment(RootComponent);
}

void ATimeBonusActor::BeginPlay()
{
	Super::BeginPlay();

	if (CurveOne != NULL)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		TimelineOne = NewObject<UTimelineComponent>(this, FName(TEXT("TimelineOne")));
		TimelineOne->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(TimelineOne);
		TimelineOne->SetNetAddressable();
		TimelineOne->SetPropertySetObject(this);

		TimelineOne->SetLooping(false);
		TimelineOne->SetTimelineLength(3.0f);
		TimelineOne->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		TimelineOne->SetPlaybackPosition(0.0f, false);
		onTimelineCallback.BindUFunction(this, FName(TEXT("OneTimelineCallback")));
		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("OneTimelineFinishedCallback")));
		TimelineOne->AddInterpFloat(CurveOne, onTimelineCallback, FName(TEXT("CurveFloatValueOne")));
		TimelineOne->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		TimelineOne->RegisterComponent();
	}

	if (CurveTwo != NULL)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		TimelineTwo = NewObject<UTimelineComponent>(this, FName(TEXT("TimelineTwo")));
		TimelineTwo->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(TimelineTwo);
		TimelineTwo->SetNetAddressable();
		TimelineTwo->SetPropertySetObject(this);

		TimelineTwo->SetLooping(false);
		TimelineTwo->SetTimelineLength(3.0f);
		TimelineTwo->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		TimelineTwo->SetPlaybackPosition(0.0f, false);
		onTimelineCallback.BindUFunction(this, FName(TEXT("TwoTimelineCallback")));
		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("TwoTimelineFinishedCallback")));
		TimelineTwo->AddInterpFloat(CurveTwo, onTimelineCallback, FName(TEXT("CurveFloatValueTwo")));
		TimelineTwo->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		TimelineTwo->RegisterComponent();
	}

	GetWorldTimerManager().SetTimer(TimerHandle_BounMeshRotator, this, &ATimeBonusActor::BounMeshRotator, 0.05f, true);
}

void ATimeBonusActor::BounMeshRotator()
{
	FRotator OldRotator = BonusMesh->GetComponentRotation();

	FRotator NewRotator(OldRotator.Pitch, OldRotator.Yaw + 100, OldRotator.Roll);

	BonusMesh->SetWorldRotation(FMath::RInterpTo(OldRotator, NewRotator, 1.0f, 0.1f));
}

void ATimeBonusActor::TiggerComponentBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	BonusMesh->SetVisibility(false, false);
	Fx->SetActive(false, false);

	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 333;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName(TEXT("ShowFunction"));
	UKismetSystemLibrary::RetriggerableDelay(this, 10.0f, LatentInfo);

	UActionTestBlueprintLibrary::DecreaseRoundDuration(this, 1.0);

	TextPlane->SetVisibility(true);

	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_HiddenTextPlane))
		GetWorldTimerManager().SetTimer(TimerHandle_HiddenTextPlane, this, &ATimeBonusActor::HiddenTextPlane, 2.0f, false);

	if (TimelineOne != NULL)
	{
		TimelineOne->PlayFromStart();
	}

	if (TimelineTwo != NULL)
	{
		TimelineTwo->PlayFromStart();
	}

}

void ATimeBonusActor::OneTimelineCallback(float val)
{
	FVector NewLoction = TextPlane->GetComponentLocation() + FVector(val * 4.0f, 0.0f, val);
	TextPlane->SetWorldLocation(NewLoction);
}

void ATimeBonusActor::TwoTimelineCallback(float val)
{
	FVector NewScale = TextPlane->RelativeScale3D + FVector(val);
	TextPlane->SetRelativeScale3D(NewScale);
}

void ATimeBonusActor::OneTimelineFinishedCallback()
{
	TextPlane->SetWorldLocation(TextPlaneLocation);
}

void ATimeBonusActor::TwoTimelineFinishedCallback()
{
	TextPlane->SetRelativeScale3D(TextPlaneScale);
}

void ATimeBonusActor::ShowFunction()
{
	BonusMesh->SetVisibility(true);
	Fx->SetActive(true);
}

void ATimeBonusActor::HiddenTextPlane()
{
	TextPlane->SetVisibility(false);
}

void ATimeBonusActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurveOne != NULL)
	{
		TimelineOne->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (CurveTwo != NULL)
	{
		TimelineTwo->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ATimeBonusActor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	TextPlane->SetVisibility(false);

	TextPlaneLocation = TextPlane->GetComponentLocation();

	TextPlaneScale = TextPlane->RelativeScale3D;
}

