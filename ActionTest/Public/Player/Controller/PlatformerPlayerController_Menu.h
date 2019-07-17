// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformerPlayerController_Menu.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API APlatformerPlayerController_Menu : public APlayerController
{
	GENERATED_UCLASS_BODY()

	/** 游戏初始化后 */
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


protected:

	/** 主菜单 */
	TSharedPtr<class FPlatformerMainMenu> PlatformerMainMenu;
};
