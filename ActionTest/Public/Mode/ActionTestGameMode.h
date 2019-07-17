// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionTestGameMode.generated.h"


namespace EGameState
{
	enum Type 
	{
		Intro,
		Waiting,
		Playing,
		Finished,
		Restarting
	};
}

/**
 * 
 */
UCLASS()
class ACTIONTEST_API AActionTestGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:

	/** 获取当前游戏的状态 */
	EGameState::Type GetGameState() const;

private:

	/** 当前正在进行中 */
	EGameState::Type GameState;
	
};
