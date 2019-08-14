// Fill out your copyright notice in the Description page of Project Settings.

#include "Elevator2Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AElevator2Actor::AElevator2Actor()
{
	GetMesh()->SetRelativeLocation(FVector(-30.0f, 0.0f, 37.0f));

	Elev = CreateDefaultSubobject<UArrowComponent>(TEXT("Elev"));

	Elev->SetupAttachment(RootComponent);

	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh1"));

	StaticMesh1->SetupAttachment(Elev);

	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh2"));

	StaticMesh2->SetupAttachment(Elev);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	Trigger->SetupAttachment(Elev);

	SoundStop = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundStop"));

	SoundStop->SetupAttachment(Elev);

	SoundStart = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundStart"));

	SoundStart->SetupAttachment(Elev);
}
