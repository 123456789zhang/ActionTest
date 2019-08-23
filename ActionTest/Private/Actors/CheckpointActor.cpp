// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointActor.h"
#include "Components/BoxComponent.h"
#include "ActionTestBlueprintLibrary.h"

ACheckpointActor::ACheckpointActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetBoxExtent(FVector(128.0f, 128.0f, 1024.0f));
	Box->SetCollisionProfileName(FName(TEXT("Custom")));
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Ignore);

	RootComponent = Box;
}

void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointActor::SetRecord(float Time, FString Name, int32 index)
{
}


void ACheckpointActor::GetRecord(float & Time, FString & Name, int32 index)
{
}

const float ACheckpointActor::GetCurrentTime()
{
	return UActionTestBlueprintLibrary::GetCurrentCheckpointTime(this,CheckPointID);
}

void ACheckpointActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	DeltaTime = UActionTestBlueprintLibrary::MarkCheckpointTime(this,CheckPointID);

	if (bIsItTheLastCheckPoint)
	{
		UActionTestBlueprintLibrary::FinishRace(this);
	}

	if (DeltaTime > 0.0)
	{
		FString Message = UActionTestBlueprintLibrary::DescribeTime(UActionTestBlueprintLibrary::GetCurrentCheckpointTime(this, CheckPointID),false);

		UActionTestBlueprintLibrary::DisplayMessage(this, Message, 4.0, 0.5f, 0.2f, 4.0f, false);

		if (DeltaTime != 0.0f)
		{
			if (bIsItTheLastCheckPoint)
			{
				FString MessageTwo = UActionTestBlueprintLibrary::DescribeTime(DeltaTime, true);
				MessageTwo = MessageTwo.Append(TEXT("TRY AGAIN"));
				UActionTestBlueprintLibrary::DisplayMessage(this, MessageTwo, 4.0, 0.5f, 0.3f, 4.0f, false);

				bWinner = false;

				bStartEnding = true;
			}
			else
			{
				FString MessageTwo = UActionTestBlueprintLibrary::DescribeTime(DeltaTime, true);
				UActionTestBlueprintLibrary::DisplayMessage(this, MessageTwo, 4.0, 0.5f, 0.3f, 4.0f, false);
			}
		}
	}
	else
	{
		FString Message = UActionTestBlueprintLibrary::DescribeTime(UActionTestBlueprintLibrary::GetCurrentCheckpointTime(this, CheckPointID), false);

		UActionTestBlueprintLibrary::DisplayMessage(this, Message, 4.0, 0.5f, 0.2f, 4.0f, false);

		if (DeltaTime != 0.0f)
		{
			FString MessageTwo = UActionTestBlueprintLibrary::DescribeTime(DeltaTime, true);
			MessageTwo = MessageTwo.Append(TEXT("NEW RECORD!!! "));
			UActionTestBlueprintLibrary::DisplayMessage(this, MessageTwo, 4.0, 0.5f, 0.3f, 4.0f, false);
		}

		if (bIsItTheLastCheckPoint)
		{
			bWinner = true;

			bStartEnding = true;
		}
	}
}

