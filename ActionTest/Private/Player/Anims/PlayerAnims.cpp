// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnims.h"
#include "ActionTestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnims::UPlayerAnims()
{
	bInSlide = false;
	bInAir = false;
	Speed = 800.0f;
}

void UPlayerAnims::NativeUpdateAnimation(float DeltaSeconds)
{
	AActionTestCharacter* Character = Cast<AActionTestCharacter>(TryGetPawnOwner());

	if (Character == nullptr)
	{
		return;
	}

	bInSlide = Character->IsSliding();

	float DotVelocity =FVector::DotProduct(Character->GetVelocity(), FVector(1.0f, 0.0f, 0.0f));

	Speed = FMath::Abs(DotVelocity);

	bInAir = Character->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling;

}
