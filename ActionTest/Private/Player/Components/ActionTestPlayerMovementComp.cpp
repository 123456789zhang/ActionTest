// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestPlayerMovementComp.h"
#include "ActionTestGameMode.h"
#include "Engine/Engine.h"
#include "ActionTestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/WorldSettings.h"

UActionTestPlayerMovementComp::UActionTestPlayerMovementComp()
{
	MinSlideSpeed = 200.f;
	MaxSlideSpeed = MaxWalkSpeed + 200.0f;
	SlideHeight = 60.0f;

	SlideVelocityReduction = 30.0f;

	SlideMeshRelativeLocationOffset = FVector(0.0f, 0.0f, 34.0f);
	bWantsSlideMeshRelativeLocationOffset = true;

	ModSpeedObstacleHit = 0.0f;
}

bool UActionTestPlayerMovementComp::IsSliding() const
{
	return bInSlide;
}

void UActionTestPlayerMovementComp::TryToEndSlide()
{
	//如果允许碰撞，结束滑动
	if (bInSlide)
	{
		if (RestoreCollisionHeightAfterSlide())
		{
			bInSlide = false;

		}
	}
}

void UActionTestPlayerMovementComp::PauseMovementForLedgeGrab()
{
	SavedSpeed = Velocity.Size() * ModSpeedObstacleHit;

	StopMovementImmediately();
	DisableMovement();
	TryToEndSlide();
}

void UActionTestPlayerMovementComp::SetMinSlideSpeed(float minSlideSpeed)
{
	MinSlideSpeed = minSlideSpeed;
}

void UActionTestPlayerMovementComp::SetSlideHeight(float slideHeight)
{
	SlideHeight = slideHeight;
}

void UActionTestPlayerMovementComp::RestoreMovement()
{
	SetMovementMode(MOVE_Walking);

	if (SavedSpeed > 0)
	{
		Velocity = PawnOwner->GetActorForwardVector() * SavedSpeed;
	}
}

void UActionTestPlayerMovementComp::PhysWalking(float deltaTime, int32 Iterations)
{
	AActionTestCharacter* MyPawn = Cast<AActionTestCharacter>(PawnOwner);

	if (MyPawn)
	{
		const bool bWantsToSlide = MyPawn->WantsToSlide();
		if (IsSliding())//玩家滑动结束
		{
			CalcCurrentSlideVelocityReduction(deltaTime);
			CalcSlideVelocity(Velocity);
			
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, 
				*FString::Printf(TEXT("Velocity x:%f y:%f z:%f SizeSquared:%f"), Velocity.X, Velocity.Y, Velocity.Z, Velocity.SizeSquared()));
			
			const float CurrentSpeedSq = Velocity.SizeSquared();
			if (CurrentSpeedSq <= FMath::Square(MinSlideSpeed))
			{
				//滑动最小值 - 尝试结束它
				TryToEndSlide();
			}
		}
		else if (bWantsToSlide)//玩家滑动
		{
			if (!IsFlying() &&
				Velocity.SizeSquared() > FMath::Square(MinSlideSpeed * 2.0f))//确保玩家有一定的速度
			{
				StartSlide();
			}
		}
	}

	Super::PhysWalking(deltaTime, Iterations);
}

FVector UActionTestPlayerMovementComp::ScaleInputAcceleration(const FVector & InputAcceleration) const
{
	FVector NewAccel = InputAcceleration;

	AActionTestGameMode* GameMode = GetWorld()->GetAuthGameMode<AActionTestGameMode>();
	if (GameMode && GameMode->IsRoundInProgress())
	{
		NewAccel.X = 1.0f;
	}

	return Super::ScaleInputAcceleration(NewAccel);
}

void UActionTestPlayerMovementComp::StartSlide()
{
	if (!bInSlide)
	{
		bInSlide = true;
		CurrentSlideVelocityReduction = 0;
		SetSlideCollisionHeight();
	
		AActionTestCharacter* MyOwner = Cast<AActionTestCharacter>(PawnOwner);
		if (MyOwner)
		{
			//播放滑动音乐
			MyOwner;
		}
	}
}

void UActionTestPlayerMovementComp::SetSlideCollisionHeight()
{
	if (!CharacterOwner || SlideHeight <= 0.0f)
	{
		return;
	}

	//如果碰撞已经在期望的大小，则不执行。
	if (CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() == SlideHeight)
	{
		return;
	}

	//碰撞大小更改为新值
	CharacterOwner->GetCapsuleComponent()->SetCapsuleSize(CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleRadius(),SlideHeight);

	//应用修正PawnOwner网相对位置
	if (bWantsSlideMeshRelativeLocationOffset)
	{
		ACharacter* DefCharacter = CharacterOwner->GetClass()->GetDefaultObject<ACharacter>();
		const FVector Correction = DefCharacter->GetMesh()->RelativeLocation + SlideMeshRelativeLocationOffset;
		CharacterOwner->GetMesh()->SetRelativeLocation(Correction);
	}
}

bool UActionTestPlayerMovementComp::RestoreCollisionHeightAfterSlide()
{
	if (!CharacterOwner || !UpdatedPrimitive)
	{
		return false;
	}

	ACharacter* DefCharacter = CharacterOwner->GetClass()->GetDefaultObject<ACharacter>();
	const float DefHalfHeight = DefCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	const float DefRadius = DefCharacter->GetCapsuleComponent()->GetUnscaledCapsuleRadius();

	//如果冲突已经达到所需的大小，则不要执行。
	if (CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() == DefHalfHeight)
	{
		return false;
	}

	const float HeightAdjust = DefHalfHeight - CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	const FVector NewLocation = CharacterOwner->GetActorLocation() + FVector(0.0f, 0.0f, HeightAdjust);

	//检查是否有足够的空间容纳默认的胶囊大小
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(FinishSlide), false, CharacterOwner);
	FCollisionResponseParams ResponseParam;

	InitCollisionParams(TraceParams, ResponseParam);
	const bool bBlocked = GetWorld()->OverlapBlockingTestByChannel(NewLocation, FQuat::Identity, UpdatedPrimitive->GetCollisionObjectType(), FCollisionShape::MakeCapsule(DefRadius, DefHalfHeight), TraceParams);
	if (bBlocked)
	{
		return false;
	}

	//恢复胶囊大小和移动到调整的位置
	CharacterOwner->TeleportTo(NewLocation, CharacterOwner->GetActorRotation(), false, true);
	CharacterOwner->GetCapsuleComponent()->SetCapsuleSize(DefRadius, DefHalfHeight);

	//恢复原始PawnOwner网格的相对位置
	if (bWantsSlideMeshRelativeLocationOffset)
	{
		CharacterOwner->GetMesh()->SetRelativeLocation(DefCharacter->GetMesh()->RelativeLocation);
	}

	return true;
}

void UActionTestPlayerMovementComp::CalcCurrentSlideVelocityReduction(float DeltaTime)
{
	float ReductionCoef = 0.0f;

	const float FloorDotVeloctiy = FVector::DotProduct(CurrentFloor.HitResult.ImpactNormal, Velocity.GetSafeNormal());
	const bool bNeedsSlopeAdjustment = (FloorDotVeloctiy != 0.0f);

	if (bNeedsSlopeAdjustment)
	{
		const float Mutiplier = 1.0f + FMath::Abs<float>(FloorDotVeloctiy);
		if (FloorDotVeloctiy > 0.0f)
		{
			ReductionCoef += SlideVelocityReduction * Mutiplier;//下坡时增加速度
		}
		else
		{
			ReductionCoef -= SlideVelocityReduction * Mutiplier;//上坡时增加速度
		}
	}
	else
	{
		ReductionCoef -= SlideVelocityReduction;//在平地上减速
	}

	float TimeDilation = GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation();
	CurrentSlideVelocityReduction += (ReductionCoef * TimeDilation * DeltaTime);
}

void UActionTestPlayerMovementComp::CalcSlideVelocity(FVector & OutVelocity) const
{
	const FVector VelocityDir = Velocity.GetSafeNormal();
	FVector NewVelocity = Velocity + CurrentSlideVelocityReduction * VelocityDir;

	const float NewSpeedSq = NewVelocity.SizeSquared();
	if (NewSpeedSq > FMath::Square(MaxSlideSpeed))
	{
		NewVelocity = VelocityDir * MaxSlideSpeed;
	}
	else if (NewSpeedSq < FMath::Square(MinSlideSpeed))
	{
		NewVelocity = VelocityDir * MinSlideSpeed;
	}

	OutVelocity = NewVelocity;
}
