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

private:

	/** 当前正在进行中 */
	EGameState::Type GameState;

	/** 如果玩家赢了这一轮，为真，否则为假 */
	uint32 bRoundWasWon : 1;

	/** 玩家开始这一轮的时间 */
	float RoundStartTime;

	/** 当前检查时间点 */
	TArray<float> CurrentTimes;

	/** 最好的检查时间 */
	TArray<float> BastTimes;

public:

	/** 准备游戏状态并显示HUD信息 */
	void PrepareRound(bool bRestarting = false);

	/** 获取当前游戏的状态 */
	EGameState::Type GetGameState() const;

	/** 设置是否可以重新开始游戏 */
	void SetCanBeRestarted(bool bAllowRestart);

	/** 如果回合正在进行中，返回true——玩家仍在移动 */
	bool IsRoundInProgress() const;

	/** 开始这一轮游戏 */
	void StartRound();

	/** 增加/减少DeltaTime一轮持续时间 */
	void ModifyRoundDuration(float DeltaTime, bool bIncrease);

	/** 获取检查点时间:当前游戏 */
	float GetCurrentCheckpointTime(int32 CheckpointID) const;

	/** 获取最好的检查点时间 */
	float GetBastCheckpointTime(int32 CheckpointID) const;

	/** 保存当前时间检查点 */
	void SaveCheckpointTime(int32 CheckpointID);

	/** 完成新一轮 */
	void FinishRound();

	/** 如果回合获胜，返回true(最佳时间) */
	bool IsRoundWon() const;

	/**
	 * 已开始的返回时间(以秒为单位)
	 * 如果回合已经结束，则返回回合持续时间
	 */
	float GetRoundDuration() const;

	/** 获取检查点数量 */
	int32 GetNumCheckpoints() const;

};
