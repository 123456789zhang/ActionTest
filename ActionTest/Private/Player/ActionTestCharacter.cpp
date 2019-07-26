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
		AnimPositionAdjustment = FMath::VInterpConstantTo(AnimPositionAdjustment,FVector::ZeroVector, DeltaSeconds,400.0f);
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

	if (GetCharacterMovement()->MovementMode != MOVE_Walking && ForwardDot < -0.9f)
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
}

void AActionTestCharacter::PlayRoundFinished()
{
}
