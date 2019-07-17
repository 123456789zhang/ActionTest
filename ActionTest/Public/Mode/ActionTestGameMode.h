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

	/** ��ȡ��ǰ��Ϸ��״̬ */
	EGameState::Type GetGameState() const;

private:

	/** ��ǰ���ڽ����� */
	EGameState::Type GameState;
	
};
