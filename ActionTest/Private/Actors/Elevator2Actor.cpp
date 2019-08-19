// Fill out your copyright notice in the Description page of Project Settings.

#include "Elevator2Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/Engine.h"


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
	Elev->SetRelativeLocation(FVector(404.33f, 1.2f, -105.7f));

	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh1"));
	StaticMesh1->SetRelativeLocation(FVector(3450.0f, 0.0f, 300.61f));
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
	Trigger->OnComponentBeginOverlap.__Internal_AddDynamic(this, &AElevator2Actor::TriggerBeginOverlap, FName(TEXT("TriggerBeginOverlap")));
	Trigger->SetupAttachment(Elev);

	SoundStop = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundStop"));
	SoundStop->SetRelativeLocation(FVector(-231.96f, 0.0f, 290.72f));
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

	PrimaryActorTick.bCanEverTick = true;
}

void AElevator2Actor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	low_position = GetMesh()->GetComponentLocation().Z;

	Trigger->AddRelativeLocation(FVector(TriggerOffset, 0.0f, 0.0f));

	Elev->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	bTempOnce = false;
}

void AElevator2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimelineComponentOne != NULL)
	{
		TimelineComponentOne->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (TimelineComponentTwo != NULL)
	{
		TimelineComponentTwo->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (TimelineComponentThree != NULL)
	{
		TimelineComponentThree->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (TimelineComponentFour != NULL)
	{
		TimelineComponentFour->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void AElevator2Actor::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineEventStatic onTimelineFinishedCallbackTwo;
	TimelineComponentTwo = NewObject<UTimelineComponent>(this, TEXT("TimelineComponentTwo"));
	TimelineComponentTwo->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	this->BlueprintCreatedComponents.Add(TimelineComponentTwo);
	TimelineComponentTwo->SetNetAddressable();
	TimelineComponentTwo->SetPropertySetObject(this);
	TimelineComponentTwo->SetLooping(false);
	TimelineComponentTwo->SetTimelineLength(10.0f);
	TimelineComponentTwo->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	TimelineComponentTwo->SetPlaybackPosition(0.0f, false);

	onTimelineFinishedCallbackTwo.BindUFunction(this, FName(TEXT("TimelineFinishedCallbackStartPlaySound")));
	TimelineComponentTwo->SetTimelineFinishedFunc(onTimelineFinishedCallbackTwo);
	TimelineComponentTwo->RegisterComponent();


	FOnTimelineEventStatic onTimelineFinishedCallbackThree;
	TimelineComponentThree = NewObject<UTimelineComponent>(this, TEXT("TimelineComponentThree"));
	TimelineComponentThree->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	this->BlueprintCreatedComponents.Add(TimelineComponentThree);
	TimelineComponentThree->SetNetAddressable();
	TimelineComponentThree->SetPropertySetObject(this);
	TimelineComponentThree->SetLooping(false);
	TimelineComponentThree->SetTimelineLength(10.0f);
	TimelineComponentThree->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	TimelineComponentThree->SetPlaybackPosition(0.0f, false);

	onTimelineFinishedCallbackThree.BindUFunction(this, FName(TEXT("TimelineFinishedCallbackStartPlaySound")));
	TimelineComponentThree->SetTimelineFinishedFunc(onTimelineFinishedCallbackThree);
	TimelineComponentThree->RegisterComponent();


	FOnTimelineEventStatic onTimelineFinishedCallbackFour;
	TimelineComponentFour = NewObject<UTimelineComponent>(this, TEXT("TimelineComponentFour"));
	TimelineComponentFour->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	this->BlueprintCreatedComponents.Add(TimelineComponentFour);
	TimelineComponentFour->SetNetAddressable();
	TimelineComponentFour->SetPropertySetObject(this);
	TimelineComponentFour->SetLooping(false);
	TimelineComponentFour->SetTimelineLength(10.0f);
	TimelineComponentFour->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	TimelineComponentFour->SetPlaybackPosition(0.0f, false);

	onTimelineFinishedCallbackFour.BindUFunction(this, FName(TEXT("TimelineFinishedCallbackTimelineOneReverse")));
	TimelineComponentFour->SetTimelineFinishedFunc(onTimelineFinishedCallbackFour);
	TimelineComponentFour->RegisterComponent();

	if (CurveOne != NULL)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		TimelineComponentOne = NewObject<UTimelineComponent>(this, TEXT("TimelineComponentOne"));
		TimelineComponentOne->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(TimelineComponentOne);
		TimelineComponentOne->SetNetAddressable();
		TimelineComponentOne->SetPropertySetObject(this);
		TimelineComponentOne->SetDirectionPropertyName(FName(TEXT("OneTimelineDirection")));

		TimelineComponentOne->SetLooping(false);
		TimelineComponentOne->SetTimelineLength(4.0f);
		TimelineComponentOne->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		TimelineComponentOne->SetPlaybackPosition(0.0f, false);

		onTimelineCallback.BindUFunction(this, FName(TEXT("TimelineCallbackElevator")));
		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("TimelineFinishedCallbackIsExecute")));
		TimelineComponentOne->AddInterpFloat(CurveOne, onTimelineCallback, FName(TEXT("CurveFloatValue")), FName(TEXT("Track")));
		TimelineComponentOne->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		TimelineComponentOne->RegisterComponent();
	}
}

void AElevator2Actor::TriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bTempOnce)
	{
		SoundStart->Play();

		if (TimelineComponentTwo != NULL)
		{
			TimelineComponentTwo->PlayFromStart();
		}

		if (TimelineComponentThree != NULL)
		{
			TimelineComponentThree->PlayFromStart();
		}

		if (TimelineComponentFour != NULL)
		{
			TimelineComponentFour->PlayFromStart();
		}

		if (TimelineComponentOne != NULL)
		{
			TimelineComponentOne->PlayFromStart();
		}
	}
}

void AElevator2Actor::TimelineCallbackElevator(float val)
{

	FVector WorldLocation = GetMesh()->GetComponentLocation();

	WorldLocation.Z = low_position + val;

	GetMesh()->SetWorldLocation(WorldLocation);
}

void AElevator2Actor::TimelineFinishedCallbackIsExecute()
{
	bTempOnce = false;
}

void AElevator2Actor::TimelineFinishedCallbackStopPlaySound()
{
	SoundStop->Play(0.0f);
}

void AElevator2Actor::TimelineFinishedCallbackTimelineOneReverse()
{
	TimelineComponentOne->Reverse();
}

void AElevator2Actor::TimelineFinishedCallbackStartPlaySound()
{
	SoundStart->FadeOut(0.0f, 0.0f);
	SoundStart->Stop();
}
