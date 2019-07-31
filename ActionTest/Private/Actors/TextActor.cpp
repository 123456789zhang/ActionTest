// Fill out your copyright notice in the Description page of Project Settings.

#include "TextActor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Engine.h"
#include "Curves/CurveFloat.h"
#include "Curves/RichCurve.h"
#include "Components/TimelineComponent.h"


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

	TempBoolGateOpenOrClose = false;

	TempBool = true;
}


void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATextActor::BeginPlay()
{
	Super::BeginPlay();

	if (FloatCurveOne != NULL)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		TimelineComponentOne = NewObject<UTimelineComponent>(this, TEXT("TimelineComponentOne"));
		TimelineComponentOne->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(TimelineComponentOne);
		TimelineComponentOne->SetNetAddressable();
		TimelineComponentOne->SetPropertySetObject(this);
		TimelineComponentOne->SetDirectionPropertyName(FName("TimelineComponentOne"));

		TimelineComponentOne->SetLooping(false);
		TimelineComponentOne->SetTimelineLength(0.5f);
		TimelineComponentOne->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		TimelineComponentOne->SetPlaybackPosition(0.0f, false);

		onTimelineCallback.BindUFunction(this, FName(TEXT("OneTimelineCallback")));
		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("OneTimelineFinishedCallback")));
		TimelineComponentOne->AddInterpFloat(FloatCurveOne, onTimelineCallback, FName(TEXT("OneCurveFloatValue")),FName(TEXT("OneTrack")));
		TimelineComponentOne->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		TimelineComponentOne->RegisterComponent();
	}

	if (FloatCurveTow != NULL)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		TimelineComponentTwo = NewObject<UTimelineComponent>(this, TEXT("TimelineComponentOne"));
		TimelineComponentTwo->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(TimelineComponentTwo);
		TimelineComponentTwo->SetNetAddressable();
		TimelineComponentTwo->SetPropertySetObject(this);
		TimelineComponentTwo->SetDirectionPropertyName(FName("TimelineComponentOne"));

		TimelineComponentTwo->SetLooping(false);
		TimelineComponentTwo->SetTimelineLength(0.5f);
		TimelineComponentTwo->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		TimelineComponentTwo->SetPlaybackPosition(0.0f, false);

		onTimelineCallback.BindUFunction(this, FName(TEXT("TwoTimelineCallback")));
		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("TwoTimelineFinishedCallback")));
		TimelineComponentTwo->AddInterpFloat(FloatCurveOne, onTimelineCallback, FName(TEXT("TwoCurveFloatValue")), FName(TEXT("TwoTrack")));
		TimelineComponentTwo->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		TimelineComponentTwo->RegisterComponent();
	}
}

void ATextActor::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Gate(1);
}

void ATextActor::OneTimelineCallback()
{
}

void ATextActor::OneTimelineFinishedCallback()
{
}

void ATextActor::TwoTimelineCallback()
{
}

void ATextActor::TwoTimelineFinishedCallback()
{
}

void ATextActor::Gate(int32 value)
{
	int32 CurrentState = value;

	do
	{
		switch (CurrentState)
		{
		case 1:
			{
				if (TempBool)
				{
					if (TempBoolGateOpenOrClose)
					{
						TempBool = false;
					}
					else 
					{
						TempBool = true;
					}
				}

				if (TempBool)
				{
					SequenceOne();
				}

				CurrentState = -1;

				break;
			}

		case 2:
			{
				CurrentState = 1;
			
				TempBool = true;

				break;
			}

		case 3:
			{
				CurrentState = 1;

				TempBool = false;

				break;
			}
		default:
			break;
		}

	} while (CurrentState != -1);
}

void ATextActor::SequenceOne()
{
	if (TimelineComponentOne != NULL)
	{
		TimelineComponentOne->Play();
	}

	Gate(3);
}

