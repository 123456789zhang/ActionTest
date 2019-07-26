// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "ActionTestPlayerMovementComp.h"

APlayerPawn::APlayerPawn()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		StaticMesh(TEXT("SkeletalMesh'/Game/Character/Skel_Mesh/Character_SkelMesh.Character_SkelMesh'"));

	ConstructorHelpers::FClassFinder<UAnimInstance>
		StaticAnim(TEXT("AnimBlueprint'/Game/Character/Anims/PlayerAnim.PlayerAnim_C'"));

	
	CrouchedEyeHeight = 64.0f;
	BaseEyeHeight = 128.0f;

	GetCapsuleComponent()->SetCapsuleRadius(68.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(176.0f);
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Yes;

	GetMesh()->SetRelativeLocation(FVector(-163.0f,0.0f,-163.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f));
	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Yes;
	if(StaticMesh.Object != nullptr)
		GetMesh()->SetSkeletalMesh(StaticMesh.Object);

	if (StaticAnim.Class != nullptr)
		GetMesh()->AnimClass = StaticAnim.Class;

	UActionTestPlayerMovementComp* MoveComp = Cast<UActionTestPlayerMovementComp>(GetCharacterMovement());
	
	MoveComp->SetMinSlideSpeed(400.0f);
	MoveComp->SetSlideHeight(135.0f);

	//Jumping/Falling
	MoveComp->JumpZVelocity = 1050.f;
	MoveComp->AirControl = 1.0f;

	//Character Movement
	MoveComp->MaxAcceleration = 640.0f;
	MoveComp->CrouchedHalfHeight = 80.0f;
	MoveComp->Mass = 200.0f;

	//Walking
	MoveComp->MaxWalkSpeed = 1500.0f;
	MoveComp->MaxWalkSpeedCrouched = 1500.0f;
	MoveComp->BrakingDecelerationWalking = 512.0f;

	//Custom Movement
	MoveComp->MaxCustomMovementSpeed = 1500.0f;

	//Nav Movement
	FNavAgentProperties  NavAgentProperties=  FNavAgentProperties(68.0f, 352.0f);
	NavAgentProperties.bCanJump = true;
	NavAgentProperties.bCanWalk = true;
	NavAgentProperties.bCanSwim = true;
	MoveComp->NavAgentProps = NavAgentProperties;
}