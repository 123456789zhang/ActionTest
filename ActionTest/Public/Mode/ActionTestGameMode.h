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

public:

	/** ��ȡ��ǰ��Ϸ��״̬ */
	EGameState::Type GetGameState() const;

	/** �����Ƿ�������¿�ʼ��Ϸ */
	void SetCanBeRestarted(bool bAllowRestart);


private:

	/** ��ǰ���ڽ����� */
	EGameState::Type GameState;
	
};
