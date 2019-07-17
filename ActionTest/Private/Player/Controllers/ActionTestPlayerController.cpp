// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestPlayerController.h"
#include "ActionTestPlayerCameraManager.h"

AActionTestPlayerController::AActionTestPlayerController()
{
	PlayerCameraManagerClass = AActionTestPlayerCameraManager::StaticClass();
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

bool AActionTestPlayerController::TryStartingGame()
{
	return false;
}
