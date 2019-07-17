// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatfromerPlayerController_Menu.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API APlatfromerPlayerController_Menu : public APlayerController
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

	TSharedPtr<class FPlatformerMainMenu> PlatformerMainMenu;
};
