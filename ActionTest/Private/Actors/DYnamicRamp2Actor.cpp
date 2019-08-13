// Fill out your copyright notice in the Description page of Project Settings.

#include "DYnamicRamp2Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

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

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetRelativeLocation(FVector(-156.0f, 0.0f, 226.0f));
	Trigger->SetRelativeScale3D(FVector(4.0f, 5.2f, 7.6f));
	Trigger->SetCollisionProfileName(FName(TEXT("Custom")));
	Trigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Trigger->SetupAttachment(RootComponent);

	FComponentBeginOverlapSignature BeginOverlap;
	BeginOverlap.__Internal_AddDynamic(this, &ADYnamicRamp2Actor::TriggerBeginOverlap, FName(TEXT("TriggerBeginOverlap")));
	Trigger->OnComponentBeginOverlap = BeginOverlap;

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

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMeshOne(TEXT("StaticMesh'/Game/Environment/meshes/SM_Roof_01.SM_Roof_01'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMeshTwo(TEXT("StaticMesh'/Game/Environment/SM_Ad_06.SM_Ad_06'"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		StaticParticleSystem(TEXT("ParticleSystem'/Game/Environment/particles/Car_explosion1.Car_explosion1'"));

	if (StaticMeshOne.Object != NULL)
	{
		StaticMesh1->SetStaticMesh(StaticMeshOne.Object);
		StaticMesh2->SetStaticMesh(StaticMeshOne.Object);
		StaticMesh3->SetStaticMesh(StaticMeshOne.Object);
	}

	if (StaticMeshTwo.Object != NULL)
	{
		StaticMesh4->SetStaticMesh(StaticMeshTwo.Object);
	}

	if (StaticParticleSystem.Object != NULL)
	{
		Explosion->SetTemplate(StaticParticleSystem.Object);
	}

	bIsBranch = true;
}


void ADYnamicRamp2Actor::BeginPlay()
{
	Super::BeginPlay();

	if (FloatCurve != NULL)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		Timeline = NewObject<UTimelineComponent>(this,TEXT("Timeline"));
		Timeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(Timeline);
		Timeline->SetNetAddressable();
		Timeline->SetPropertySetObject(this);
		Timeline->SetDirectionPropertyName(FName("TimelineDirection"));

		Timeline->SetLooping(false);
		Timeline->SetTimelineLength(1.0f);
		Timeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		Timeline->SetPlaybackPosition(0.0f, false);
		onTimelineCallback.BindUFunction(this, FName(TEXT("TimelineCallback")));
		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("TimelineFinishedCallback")));
		Timeline->AddInterpFloat(FloatCurve, onTimelineCallback, FName(TEXT("CurveFloatValue")), FName(TEXT("Track")));
		Timeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		Timeline->RegisterComponent();
	}

	
}

void ADYnamicRamp2Actor::TriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsBranch)
	{
		GetWorldTimerManager().SetTimer(TimeHanlde_FlatFalling, this, &ADYnamicRamp2Actor::FlatFalling, 0.25f, false);
	}
}


void ADYnamicRamp2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Timeline != NULL)
	{
		Timeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ADYnamicRamp2Actor::FlatFalling()
{
	Explosion->SetActive(true);

	Timeline->PlayFromStart();
}

void ADYnamicRamp2Actor::ResetPivot()
{
	Pirvot->SetWorldRotation(FRotator(0.0f));
}

void ADYnamicRamp2Actor::TimelineCallback(float val)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETimelineDirection"), true);

	if (EnumPtr)
	{
		FName EnumName=EnumPtr->GetNameByValue((int64)(TimelineDirection));
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("TimelineDirection:%s"), *EnumName.ToString()));
	}

	FRotator Rotator(val,0.0f,0.0f);
	Pirvot->SetWorldRotation(Rotator);
}

void ADYnamicRamp2Actor::TimelineFinishedCallback()
{
	GetWorldTimerManager().SetTimer(TimeHanlde_ResetPivot, this, &ADYnamicRamp2Actor::ResetPivot, 15.0f, false);
}

