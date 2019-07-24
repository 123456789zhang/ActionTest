// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestPlayerMovementComp.h"
#include "ActionTestGameMode.h"
#include "Engine/Engine.h"

UActionTestPlayerMovementComp::UActionTestPlayerMovementComp()
{

}

bool UActionTestPlayerMovementComp::IsSliding() const
{
	return false;
}

void UActionTestPlayerMovementComp::TryToEndSlide()
{
}

void UActionTestPlayerMovementComp::PauseMovementForLedgeGrab()
{
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
