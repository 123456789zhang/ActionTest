// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGame_Menu.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API APlatformerGame_Menu : public AGameModeBase
{
	GENERATED_UCLASS_BODY()


	virtual void RestartPlayer(AController* NewPlayer) override;
};
