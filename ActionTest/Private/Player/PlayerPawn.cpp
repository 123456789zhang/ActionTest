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

	UActionTestPlayerMovementComp* MoveComp = Cast<UActionTestPlayerMovementComp>(GetCharacterMovement());
	
	MoveComp->MaxAcceleration = 640.0f;
	MoveComp->CrouchedHalfHeight = 80.0f;
	MoveComp->Mass = 200.0f;

	MoveComp->MaxWalkSpeed = 1500.0f;
	MoveComp->MinAnalogWalkSpeed = 1500.0f;
	MoveComp->BrakingDecelerationWalking = 512.0f;

	MoveComp->JumpZVelocity = 1050.0f;
	MoveComp->AirControl = 1.0f;

	MoveComp->MaxCustomMovementSpeed = 1500.0f;

	MoveComp->NavAgentProps = FNavAgentProperties(68.0f,352.0f);
}