// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionTestGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundFinishedDelegate);

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


	/** 委派广播游戏的结束 */
	UPROPERTY(BlueprintAssignable)
		FRoundFinishedDelegate OnRoundFinished;

	/** 全屏图片信息 */
	class FActionTestPicture* ActionTestPicture;

public:

	/** 获取当前游戏的状态 */
	EGameState::Type GetGameState() const;

	/** 设置是否可以重新开始游戏 */
	void SetCanBeRestarted(bool bAllowRestart);


private:

	/** 当前正在进行中 */
	EGameState::Type GameState;
	
};
