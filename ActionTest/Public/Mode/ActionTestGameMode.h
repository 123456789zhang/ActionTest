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


	/** ί�ɹ㲥��Ϸ�Ľ��� */
	UPROPERTY(BlueprintAssignable)
		FRoundFinishedDelegate OnRoundFinished;

	/** ȫ��ͼƬ��Ϣ */
	class FActionTestPicture* ActionTestPicture;

private:

	/** Ϊ��Ч����ʱ�� */
	FTimerHandle TimerHandle_StartRound;

	/** ��ǰ���ڽ����� */
	EGameState::Type GameState;

	/** ������Ӯ����һ�֣�Ϊ�棬����Ϊ�� */
	uint32 bRoundWasWon : 1;

	/** ��ҿ�ʼ��һ�ֵ�ʱ�� */
	float RoundStartTime;

	/** ��ǰ���ʱ��� */
	TArray<float> CurrentTimes;

	/** ��õļ��ʱ�� */
	TArray<float> BastTimes;

	/** ����غϽ�����������¿�ʼ����Ϊ�� */
	uint32 bCanBeRestarted : 1;

public:

	/** ׼����Ϸ״̬����ʾHUD��Ϣ */
	void PrepareRound(bool bRestarting = false);

	/** ��ȡ��ǰ��Ϸ��״̬ */
	EGameState::Type GetGameState() const;

	/** �����Ƿ�������¿�ʼ��Ϸ */
	void SetCanBeRestarted(bool bAllowRestart);

	/** ����غ����ڽ����У�����true������������ƶ� */
	bool IsRoundInProgress() const;

	/** ��ʼ��һ����Ϸ */
	void StartRound();

	/** ����/����DeltaTimeһ�ֳ���ʱ�� */
	void ModifyRoundDuration(float DeltaTime, bool bIncrease);

	/** ��ȡ����ʱ��:��ǰ��Ϸ */
	float GetCurrentCheckpointTime(int32 CheckpointID) const;

	/** ��ȡ��õļ���ʱ�� */
	float GetBestCheckpointTime(int32 CheckpointID) const;

	/** ���浱ǰʱ����� */
	void SaveCheckpointTime(int32 CheckpointID);

	/** �����һ�� */
	void FinishRound();

	/** ����غϻ�ʤ������true(���ʱ��) */
	bool IsRoundWon() const;

	/**
	 * �ѿ�ʼ�ķ���ʱ��(����Ϊ��λ)
	 * ����غ��Ѿ��������򷵻ػغϳ���ʱ��
	 */
	float GetRoundDuration() const;

	/** ��ȡ�������� */
	int32 GetNumCheckpoints() const;

	/** ������������������򷵻� */
	bool CanBeRestarted() const;

	/** ������������ */
	void TryRestartRound();

};
