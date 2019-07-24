// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestPlayerController.h"
#include "ActionTestPlayerCameraManager.h"
#include "ActionTestGameMode.h"
#include "Engine/Engine.h"

AActionTestPlayerController::AActionTestPlayerController()
{
	PlayerCameraManagerClass = AActionTestPlayerCameraManager::StaticClass();
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

bool AActionTestPlayerController::TryStartingGame()
{
	AActionTestGameMode* MyGame = GetWorld()->GetAuthGameMode<AActionTestGameMode>();
	if (MyGame)
	{
		const EGameState::Type GameState = MyGame->GetGameState();
		switch (GameState)
		{
			case EGameState::Waiting:
				MyGame->StartRound();
				return true;

			case EGameState::Finished:

				return true;
		}
	}
	return false;
}
