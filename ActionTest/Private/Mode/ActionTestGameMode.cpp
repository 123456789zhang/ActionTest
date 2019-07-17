// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestGameMode.h"
#include "ActionTestPlayerController.h"
#include "ActionTestHUD.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "PlayerPawn.h"

AActionTestGameMode::AActionTestGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerControllerClass = AActionTestPlayerController::StaticClass();

	HUDClass = AActionTestHUD::StaticClass();

	DefaultPawnClass = APlayerPawn::StaticClass();

	if ((GEngine != NULL) && (GEngine->GameViewport != NULL))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}


EGameState::Type AActionTestGameMode::GetGameState() const
{
	return GameState;
}
