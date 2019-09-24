// Fill out your copyright notice in the Description page of Project Settings.

#include "ZoomActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ActionTestPlayerCameraManager.h"
#include "ActionTestBlueprintLibrary.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

AZoomActor::AZoomActor()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	Box->SetBoxExtent(FVector(256.0f));
	Box->SetHiddenInGame(false);
	Box->SetCollisionProfileName(FName(TEXT("Custom")));
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Ignore);

	FComponentBeginOverlapSignature BeginOverlapSignature;
	BeginOverlapSignature.__Internal_AddDynamic(this, &AZoomActor::BoxBeginOverlap,FName(TEXT("BoxBeginOverlap")));
	Box->OnComponentBeginOverlap = BeginOverlapSignature;

	FComponentEndOverlapSignature EndOverlapSignature;
	EndOverlapSignature.__Internal_AddDynamic(this, &AZoomActor::BoxEndOverlap, FName(TEXT("BoxEndOverlap")));
	Box->OnComponentEndOverlap = EndOverlapSignature;

	RootComponent = Box;

	bZoomInFirst = false;
	ZoomSpeed = 0.0025f;
}

void AZoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZoomActor::BoxBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AActionTestPlayerCameraManager* PlayCamera  =  Cast<AActionTestPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(this, 0));
	Camera_Zoom = PlayCamera->GetCameraZoom();
	Zoom_backup = PlayCamera->GetCameraZoom();
	if (bZoomInFirst)
	{
		Camera_ZoomDirection = -1;
	}
	else
	{
		Camera_ZoomDirection = 1;
	}

	ExecuteSwitch(4);
}

void AZoomActor::BoxEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (bZoomInFirst)
	{
		Camera_ZoomDirection = 1;
	}
	else
	{
		Camera_ZoomDirection = -1;
	}
	ExecuteSwitch(4);
}

void AZoomActor::CameraMobile()
{
	AActionTestPlayerCameraManager* PlayCamera = Cast<AActionTestPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(this, 0));
	PlayCamera->SetCameraZoom(Camera_Zoom);
	if (Camera_ZoomDirection > 0)
	{
		Camera_Zoom = Camera_Zoom + ZoomSpeed;

		if (bZoomInFirst)
		{
			if (Zoom_backup > Camera_Zoom)
			{
				Camera_Zoom = Zoom_backup;
			}
			else
			{
				//重新调用
				ExecuteSwitch(4);
			}
		}
		else
		{
			if (Camera_Zoom > 1.2)
			{
				Camera_Zoom = 0.9;
			}
			else
			{
				//重新调用
				ExecuteSwitch(4);
			}
		}
	}
	else
	{
		Camera_Zoom = Camera_Zoom - ZoomSpeed;

		if (bZoomInFirst)
		{
			if (Camera_Zoom < 0.0f)
			{
				Camera_Zoom = 0.53f;
			}
			else
			{
				//重新调用
				ExecuteSwitch(4);
			}
		}
		else
		{
			if (Camera_Zoom < Zoom_backup)
			{
				Camera_Zoom = Zoom_backup;
			}
			else
			{
				//重新调用
				ExecuteSwitch(4);
			}
		}
	}


}

void AZoomActor::ExecuteSwitch(int32 EntryPoint)
{
	int currentState = EntryPoint;
	do
	{
		switch (currentState)
		{
		case 1:
			CameraMobile();
			currentState = -1;
			break;
		case 2:
			UKismetSystemLibrary::RetriggerableDelay(this,0.01f,FLatentActionInfo(3,6546465,TEXT("ExecuteSwitch"),this));
			currentState = -1;
			break;

		case 3:
			currentState = 1;
			break;

		case 4:
			currentState = 2;
			break;
		default:
			break;
		}

	} while (currentState != -1);
}


