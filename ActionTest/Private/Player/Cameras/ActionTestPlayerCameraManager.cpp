// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestPlayerCameraManager.h"
#include "ActionTestCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

AActionTestPlayerCameraManager::AActionTestPlayerCameraManager()
{
	MinCameraZoomOffset = FVector(240.0f, 600.0f, 0.0f);
	MaxCameraZoomOffset = MinCameraZoomOffset * 4.0f;
	CurrentZoomAlpha = 0.1f;

	DesiredCameraOffsetZ = 0.0f;
	CurrentCameraOffsetZ = 0.0f;
	CameraOffsetInterpSpeed = 5.0f;

	CameraFixedRotation = FRotator(0.0f, -90.0f, 0.0f);
	FixedCameraOffsetZ = 130.0f;
}

void AActionTestPlayerCameraManager::SetCameraZoom(float ZoomAlpha)
{
	CurrentZoomAlpha = FMath::Clamp(ZoomAlpha, 0.0f, 1.0f);
}

void AActionTestPlayerCameraManager::SetFixedCameraOffsetZ(float InOffset)
{
	FixedCameraOffsetZ = InOffset;
}

void AActionTestPlayerCameraManager::UpdateViewTargetInternal(FTViewTarget & OutVT, float DeltaTime)
{
	FVector ViewLoc;
	FRotator ViewRot;
	OutVT.Target->GetActorEyesViewPoint(ViewLoc, ViewRot);
	ViewLoc.Z = CalcCameraOffsetZ(DeltaTime);
	ViewLoc.Z += FixedCameraOffsetZ;

	FVector CurrentCameraZoomOffset = MinCameraZoomOffset + CurrentZoomAlpha * (MaxCameraZoomOffset - MinCameraZoomOffset);
	OutVT.POV.Location = ViewLoc + CurrentCameraZoomOffset;
	OutVT.POV.Rotation = CameraFixedRotation;
}

float AActionTestPlayerCameraManager::CalcCameraOffsetZ(float DeltaTime)
{
	AActionTestCharacter* MyPawn = PCOwner ? Cast<AActionTestCharacter>(PCOwner->GetPawn()) : NULL;
	if (MyPawn)
	{
		float LocZ = MyPawn->GetActorLocation().Z;//获取玩家pawn的z轴位置
		if (MyPawn->GetCharacterMovement() && MyPawn->GetCharacterMovement()->IsFalling()) //判断是否玩家pawn在空中
		{
			if (LocZ < DesiredCameraOffsetZ)
			{
				DesiredCameraOffsetZ = LocZ;
			}
			else if (LocZ > DesiredCameraOffsetZ + MyPawn->GetCameraHeightChangeThreshold())
			{
				DesiredCameraOffsetZ = LocZ;
			}
		}
		else
		{
			DesiredCameraOffsetZ = LocZ;
		}
	}

	if (CurrentCameraOffsetZ != DesiredCameraOffsetZ)
	{
		CurrentCameraOffsetZ = FMath::FInterpTo(CurrentCameraOffsetZ, DesiredCameraOffsetZ, DeltaTime, CameraOffsetInterpSpeed);
	}

	return CurrentCameraOffsetZ;
}
