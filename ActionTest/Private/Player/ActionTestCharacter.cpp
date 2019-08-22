// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ActionTestPlayerMovementComp.h"
#include "ActionTest.h"
#include "TimerManager.h"
#include "ActionTestGameMode.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "ActionTestPlayerController.h"
#include "Engine/Engine.h"
#include "ActionTestClimbMarker.h"
#include "Components/CapsuleComponent.h"

AActionTestCharacter::AActionTestCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UActionTestPlayerMovementComp>(ACharacter::CharacterMovementComponentName))
{
	MinSpeedForHittingWall = 200;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void AActionTestCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//设置初始化的旋转
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

void AActionTestCharacter::Tick(float DeltaSeconds)
{
	if (!AnimPositionAdjustment.IsNearlyZero())
	{
		AnimPositionAdjustment = FMath::VInterpConstantTo(AnimPositionAdjustment, FVector::ZeroVector, DeltaSeconds, 400.0f);
		GetMesh()->SetRelativeLocation(GetBaseTranslationOffset() + AnimPositionAdjustment);
	}

	if (ClimbToMarker)
	{
		const FVector AdjustDelta = ClimbToMarker->GetComponentLocation() - ClimbToMarkerLoaction;
		if (!AdjustDelta.IsZero())
		{
			SetActorLocation(GetActorLocation() + AdjustDelta, false);
			ClimbToMarkerLoaction += AdjustDelta;
		}
	}


	Super::Tick(DeltaSeconds);
}

void AActionTestCharacter::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	InputComponent->BindAction("Jump", IE_Pressed, this, &AActionTestCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AActionTestCharacter::OnStopJump);
	InputComponent->BindAction("Slide", IE_Pressed, this, &AActionTestCharacter::OnStartSlide);
	InputComponent->BindAction("Slide", IE_Released, this, &AActionTestCharacter::OnStopSlide);
}

void AActionTestCharacter::CheckJumpInput(float DeltaTime)
{
	if (bPressedJump)
	{
		UActionTestPlayerMovementComp* MoveComp = Cast<UActionTestPlayerMovementComp>(GetCharacterMovement());
		if (MoveComp && MoveComp->IsSliding())
		{
			MoveComp->TryToEndSlide();
			return;
		}
	}
	Super::CheckJumpInput(DeltaTime);
}

void AActionTestCharacter::MoveBlockedBy(const FHitResult & Impact)
{
	const float ForwardDot = FVector::DotProduct(Impact.Normal, FVector::ForwardVector);
	if (GetCharacterMovement()->MovementMode != MOVE_None)
	{
		UE_LOG(LogActionTest, Log, TEXT("Collision with %s,normal = (%f,%f,%f),doc = %f, %s"),
			*GetNameSafe(Impact.Actor.Get()),
			Impact.Normal.X, Impact.Normal.Y, Impact.Normal.Z,
			ForwardDot,
			*GetCharacterMovement()->GetMovementName());
	}

	if (GetCharacterMovement()->MovementMode == MOVE_Walking && ForwardDot < -0.9f)
	{
		UActionTestPlayerMovementComp* MyMovement = Cast<UActionTestPlayerMovementComp>(GetCharacterMovement());
		const float Speed = FMath::Abs(FVector::DotProduct(MyMovement->Velocity, FVector::ForwardVector));
		//如果跑步或滑动:玩碰撞反应和跳过障碍

		float Duration = 0.01f;
		if (Speed > MinSpeedForHittingWall)
		{
			Duration = PlayAnimMontage(HitWallMontage);
		}
		GetWorldTimerManager().SetTimer(TimerHandle_ClimbOverObstacle, this, &AActionTestCharacter::ClimbOverObstacle, Duration, false);
		MyMovement->PauseMovementForLedgeGrab();
	}
	else if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		//如果在半空:试着爬到界标上
		AActionTestClimbMarker* Marker = Cast<AActionTestClimbMarker>(Impact.Actor.Get());
		if (Marker)
		{
			ClimbToLedge(Marker);

			UActionTestPlayerMovementComp* MyMovement = Cast<UActionTestPlayerMovementComp>(GetCharacterMovement());
			MyMovement->PauseMovementForLedgeGrab();
		}
	}
}

void AActionTestCharacter::Landed(const FHitResult & Hit)
{
	Super::Landed(Hit);

	AActionTestGameMode* MyGame = GetWorld()->GetAuthGameMode<AActionTestGameMode>();
	if (MyGame && MyGame->GetGameState() == EGameState::Finished)
	{
		PlayRoundFinished();
	}
}

void AActionTestCharacter::OnRoundFinished()
{
	//不在半空中停下来，我们会在着陆时继续通知你 [Landed()]
	if (GetCharacterMovement()->MovementMode != MOVE_Falling)
	{
		PlayRoundFinished();
	}
}

void AActionTestCharacter::OnRoundReset()
{
	//重置动画
	if (GetMesh() && GetMesh()->AnimScriptInstance)
	{
		GetMesh()->AnimScriptInstance->Montage_Stop(0.0f);
	}

	//重置movement属性
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	bPressedJump = false;
	bPressedSlide = false;
}

void AActionTestCharacter::PlaySlideFinished()
{
	//停止播放滑动的音乐
}

bool AActionTestCharacter::IsSliding() const
{
	UActionTestPlayerMovementComp* MoveComp = Cast<UActionTestPlayerMovementComp>(GetCharacterMovement());
	return MoveComp && MoveComp->IsSliding();
}

bool AActionTestCharacter::WantsToSlide() const
{
	return bPressedSlide;
}

float AActionTestCharacter::GetCameraHeightChangeThreshold() const
{
	return CameraHeightChangeThreshold;
}

void AActionTestCharacter::OnStartJump()
{
	AActionTestGameMode* const MyGame = GetWorld()->GetAuthGameMode<AActionTestGameMode>();
	AActionTestPlayerController* MyPC = Cast<AActionTestPlayerController>(Controller);
	if (MyPC)
	{
		if (MyPC->TryStartingGame())
		{
			return;
		}

		if (!MyPC->IsMoveInputIgnored() &&
			MyGame && MyGame->IsRoundInProgress())
		{
			bPressedJump = true;
		}
	}
}

void AActionTestCharacter::OnStopJump()
{
	StopJumping();
}

void AActionTestCharacter::OnStartSlide()
{
	AActionTestGameMode* MyGame = GetWorld()->GetAuthGameMode<AActionTestGameMode>();
	AActionTestPlayerController* MyPC = Cast<AActionTestPlayerController>(Controller);
	if (MyPC)
	{
		if (MyPC->TryStartingGame())
		{
			return;
		}

		if (!MyPC->IsMoveInputIgnored() &&
			MyGame&& MyGame->IsRoundInProgress())
		{
			bPressedSlide = true;
		}
	}
}

void AActionTestCharacter::OnStopSlide()
{
	bPressedSlide = false;
}

void AActionTestCharacter::ClimbOverObstacle()
{
	//爬障碍:
	//-有三个动画与三种预定义的障碍高度匹配
	//-玩家移动使用根运动，结束在顶部的障碍作为动画结束

	const FVector ForwardDir = GetActorForwardVector();
	const FVector TraceStart = GetActorLocation() + ForwardDir * 150.0f + FVector(0, 0, 1) * (GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 150.0f);
	const FVector TraceEnd = TraceStart + FVector(0, 0, -1) * 500.0f;

	FCollisionQueryParams TraceParams(NAME_None, FCollisionQueryParams::GetUnknownStatId(), true);
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Pawn, TraceParams);

	if (Hit.bBlockingHit)
	{
		const FVector DestPosition = Hit.ImpactPoint + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		const float ZDiff = DestPosition.Z - GetActorLocation().Z;
		UE_LOG(LogActionTest, Log, TEXT("Climb over obstacle, Z difference: %f (%s)"), ZDiff,
			(ZDiff < ClimbOverMidHeight) ? TEXT("small") : (ZDiff < ClimbOverBigHeight) ? TEXT("mid") : TEXT("big"));

		UAnimMontage* Montage = (ZDiff < ClimbOverMidHeight) ? ClimbOverSmallMontage : (ZDiff < ClimbOverBigHeight) ? ClimbOverMidMontage : ClimbOverBigMontage;

		//设置飞行模式，因为它需要Z变化。如果走路或跌倒，我们将不能应用Z变化
		//这将在恢复运动中重置
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		SetActorEnableCollision(false);
		const float Duration = PlayAnimMontage(Montage);
		GetWorldTimerManager().SetTimer(TimerHandle_ResumeMovement, this, &AActionTestCharacter::ResumeMovement, Duration, false);
	}
	else
	{
		ResumeMovement();
	}
}

void AActionTestCharacter::PlayRoundFinished()
{
}

void AActionTestCharacter::ResumeMovement()
{
	SetActorEnableCollision(true);

	//恢复运动状态和保存的速度
	UActionTestPlayerMovementComp* MyMovement = Cast<UActionTestPlayerMovementComp>(GetCharacterMovement());
	MyMovement->RestoreMovement();

	ClimbToMarker = NULL;
}

void AActionTestCharacter::ClimbToLedge(const AActionTestClimbMarker * Marker)
{
	ClimbToMarker = Marker ? Marker->FindComponentByClass<UStaticMeshComponent>() : NULL;
	ClimbToMarkerLoaction = ClimbToMarker ? ClimbToMarker->GetComponentLocation() : FVector::ZeroVector;

	//放置于标记的左上角，但保留当前的Y坐标
	const FBox MarkerBox = Marker->GetMesh()->Bounds.GetBox();
	const FVector DesiredPosition(MarkerBox.Min.X, GetActorLocation().Y, MarkerBox.Max.Z);

	//爬上岩架:
	// -兵被放置在顶部的窗台(使用爬升抓取偏移量抵消从抓斗点)立即
	// - AnimPositionAdjustment修改网格的相对位置来平滑过渡
	//(网格从大致相同的位置开始，额外的偏移量在Tick中迅速减小到零)

	const FVector StartPosition = GetActorLocation();
	FVector AdjustedPosition = DesiredPosition;
	AdjustedPosition.X += (ClimbLedgeGrabOffsetX * GetMesh()->RelativeScale3D.X) - GetBaseTranslationOffset().X;
	AdjustedPosition.Z += GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	TeleportTo(AdjustedPosition, GetActorRotation(), false, true);

	AnimPositionAdjustment = StartPosition - (GetActorLocation() - (ClimbLedgeRootOffset * GetMesh()->RelativeScale3D));
	GetMesh()->SetRelativeLocation(GetBaseTranslationOffset() + AnimPositionAdjustment);

	const float Duration = PlayAnimMontage(ClimbLedgeMontage);
	GetWorldTimerManager().SetTimer(TimerHandle_ResumeMovement, this, &AActionTestCharacter::ResumeMovement, Duration - 0.1f, false);
}
