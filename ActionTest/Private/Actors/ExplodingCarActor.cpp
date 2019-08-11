// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplodingCarActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "ActionTestCharacter.h"
#include "TimerManager.h"


AExplodingCarActor::AExplodingCarActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		StaticParticleSystem(TEXT("ParticleSystem'/Game/Environment/particles/Explosion_2.Explosion_2'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMeshCar (TEXT("StaticMesh'/Game/Environment/Car_Cabriolet_01.Car_Cabriolet_01'"));

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>
		StaticMaterialCar(TEXT("MaterialInstanceConstant'/Game/Environment/materials/M_Car_Cabriolet_05.M_Car_Cabriolet_05'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticMaskMesh(TEXT("StaticMesh'/Game/Environment/Car_Cabriolet_01_front_flap.Car_Cabriolet_01_front_flap'"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticRoofBackMesh(TEXT("StaticMesh'/Game/Environment/Car_Cabriolet_01_roof_a.Car_Cabriolet_01_roof_a'"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		StaticRoofTopMesh(TEXT("StaticMesh'/Game/Environment/Car_Cabriolet_01_roof_b.Car_Cabriolet_01_roof_b'"));

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>
		StaticMaterial(TEXT("MaterialInstanceConstant'/Game/Environment/materials/M_Car_Cabriolet_03.M_Car_Cabriolet_03'"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetMobility(EComponentMobility::Movable);
	
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
	FComponentBeginOverlapSignature ColissionOverlapSignature;
	ColissionOverlapSignature.__Internal_AddDynamic(this,&AExplodingCarActor::OnColissionBeginOverlap,FName(TEXT("OnColissionBeginOverlap")));
	Colission->OnComponentBeginOverlap = ColissionOverlapSignature;

	CloseContactTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CloseContactTrigger"));
	CloseContactTrigger->SetRelativeLocation(FVector(-214.00456, 0.0, 82.048523));
	CloseContactTrigger->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));
	CloseContactTrigger->SetBoxExtent(FVector(32.0f, 96.0f, 48.0f));
	CloseContactTrigger->SetCollisionProfileName(FName(TEXT("OverlapAllDynamic")));
	FComponentBeginOverlapSignature CloseOverlapSignature;
	CloseOverlapSignature.__Internal_AddDynamic(this, &AExplodingCarActor::OnCloseContactTriggerBeginOverlap, FName(TEXT("OnCloseContactTriggerBeginOverlap")));
	CloseContactTrigger->OnComponentBeginOverlap = CloseOverlapSignature;

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	Explosion->SetRelativeRotation(FRotator(90.0f,0.0f,0.0f));
	Explosion->bAutoActivate = false;
	Explosion->SetMobility(EComponentMobility::Movable);
	if (StaticParticleSystem.Object != NULL)
	{
		Explosion->SetTemplate(StaticParticleSystem.Object);
	}
	
	

	Mask = CreateDefaultSubobject<UStaticMeshComponent>("Mask");
	Mask->SetRelativeTransform(FTransform(FRotator(-11.25f,0.0f,0.0f),FVector(110.669662f,0.0,121.015976f), FVector(1.0f)));
	if (StaticMaskMesh.Object != NULL && StaticMaterialCar.Object != NULL)
	{
		Mask->SetStaticMesh(StaticMaskMesh.Object);
		Mask->SetMaterial(0, StaticMaterialCar.Object);
	}

	RoofBack = CreateDefaultSubobject<UStaticMeshComponent>("RoofBack");
	RoofBack->SetRelativeTransform(FTransform(FRotator(0.0f,0.000421f, 0.0f), FVector(-174.20498, 0.0, 124.332275f), FVector(1.0f)));
	if (StaticRoofBackMesh.Object != NULL)
	{
		RoofBack->SetStaticMesh(StaticRoofBackMesh.Object);
		RoofBack->SetMaterial(0, StaticMaterial.Object);
	}
	

	RoofTop = CreateDefaultSubobject<UStaticMeshComponent>("RoofTop");
	RoofTop->SetRelativeTransform(FTransform(FRotator(0.0f), FVector(-48.540855f, 0.000061, 154.616699f), FVector(1.0f)));
	if (StaticRoofTopMesh.Object != NULL)
	{
		RoofTop->SetStaticMesh(StaticRoofTopMesh.Object);
		RoofTop->SetMaterial(0, StaticMaterial.Object);
	}
	

	RootComponent = Mesh;

	Box1->SetupAttachment(RootComponent);

	Colission->SetupAttachment(RootComponent);

	CloseContactTrigger->SetupAttachment(RootComponent);

	Explosion->SetupAttachment(RootComponent);

	Mask->SetupAttachment(RootComponent);

	RoofBack->SetupAttachment(RootComponent);

	RoofTop->SetupAttachment(RootComponent);

	LaunchSpeed = 2200.0f;
}


void AExplodingCarActor::BeginPlay()
{
	Super::BeginPlay();

	if (FloatCurve != NULL)
	{
		FOnTimelineFloat onTimeLineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		TimelineComponent = NewObject<UTimelineComponent>(this, TEXT("TimelineComponent"));
		TimelineComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(TimelineComponent);
		TimelineComponent->SetNetAddressable();
		TimelineComponent->SetPropertySetObject(this);
		TimelineComponent->SetDirectionPropertyName(FName("TimelineDirection"));

		TimelineComponent->SetLooping(false);
		TimelineComponent->SetTimelineLength(1.0f);
		TimelineComponent->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		TimelineComponent->SetPlaybackPosition(0.0f, false);

		onTimeLineCallback.BindUFunction(this, FName(TEXT("TimelineCallback")));
		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("TimelineFinishedCallback")));
		TimelineComponent->AddInterpFloat(FloatCurve,onTimeLineCallback,FName(TEXT("CurveFloatValue")),FName(TEXT("Track")));
		TimelineComponent->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		TimelineComponent->RegisterComponent();

	}
	
}

void AExplodingCarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimelineComponent != NULL)
	{
		TimelineComponent->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void AExplodingCarActor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	MaskRotation = Mask->GetComponentRotation();

	RoofBackRotation = RoofBack->GetComponentRotation();

	RoofMidRotation = RoofTop->GetComponentRotation();

	TempBool = true;

	TempBoolGateOpenOrClose = false;
}

void AExplodingCarActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Gate(1);

	Super::NotifyActorBeginOverlap(OtherActor);
}

void AExplodingCarActor::OnColissionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Gate(1);
}

void AExplodingCarActor::OnCloseContactTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Gate(3);

	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_ResetObject))
	{
		GetWorldTimerManager().SetTimer(TimerHandle_ResetObject, this, &AExplodingCarActor::ResetObject, 10.0f, false);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_ResetObject);
		GetWorldTimerManager().SetTimer(TimerHandle_ResetObject, this, &AExplodingCarActor::ResetObject, 10.0f, false);
	}
}

void AExplodingCarActor::TimelineCallback(float val)
{
	FRotator MaskRotator(val,0.0f,0.0f);
	Mask->AddLocalRotation(MaskRotator);

	FRotator RoofBRotator((val * -0.12f), 0.0f, 0.0f);
	RoofBack->AddLocalRotation(RoofBRotator);

	FVector RoofTVector(0.0f,0.0f,(val * -0.1f));
	RoofTop->AddLocalOffset(RoofTVector);
}

void AExplodingCarActor::TimelineFinishedCallback()
{

}

void AExplodingCarActor::LaunchCharacter()
{
	APawn* Pawn=UGameplayStatics::GetPlayerPawn(this,0);

	AActionTestCharacter* Character = Cast<AActionTestCharacter>(Pawn);

	Character->LaunchCharacter(FVector(0.0f, 0.0f, LaunchSpeed),false,true);
}

void AExplodingCarActor::ResetObject()
{
	Mask->SetWorldRotation(MaskRotation);
	RoofBack->SetWorldRotation(RoofBackRotation);
	RoofTop->SetWorldRotation(RoofMidRotation);
}

void AExplodingCarActor::Gate(int32 val)
{
	int32 CurrentState = val;

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
						if (TempBoolGateOpenOrClose)
						{
							TempBool = false;
						}
						else
						{
							TempBool = true;
						}
					}
				}

				if (TempBool)
				{
					SequenceMethod();
				}
					
				CurrentState = -1;

				break;

			}
		case 2: //Open
			{
				CurrentState = 1;

				TempBool = true;

				break;
			}
		case 3: //close
			{
				CurrentState = 1;

				TempBool = false;

				break;
			}
		}

	} while (CurrentState != -1);
	
}

void AExplodingCarActor::SequenceMethod()
{

	UGameplayStatics::SpawnSoundAttached(NULL, Explosion, NAME_None, FVector(0.0f), FRotator(0.0f), EAttachLocation::KeepRelativeOffset, false, 1.3f, 1.0f, 0.0f);

	Explosion->Activate(false);

	UGameplayStatics::SpawnSoundAttached(NULL, Explosion, NAME_None, FVector(0.0f), FRotator(0.0f), EAttachLocation::KeepRelativeOffset, false, 0.3f, 1.3f, 0.0f);

	TimelineComponent->PlayFromStart();

	GetWorldTimerManager().SetTimer(TimerHandle_LaunchCharacter, this, &AExplodingCarActor::LaunchCharacter, 0.1f, false);

	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_ResetObject))
	{
		GetWorldTimerManager().SetTimer(TimerHandle_ResetObject, this, &AExplodingCarActor::ResetObject, 10.0f, false);
	}
	else 
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_ResetObject);
		GetWorldTimerManager().SetTimer(TimerHandle_ResetObject, this, &AExplodingCarActor::ResetObject, 10.0f, false);
	}


	Gate(3);
}

