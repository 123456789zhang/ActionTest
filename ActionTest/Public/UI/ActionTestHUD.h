// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ActionTestHUD.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHighscoreNameAccepted, const FString&, NewHighscoreName);
/**
 * 
 */
UCLASS()
class ACTIONTEST_API AActionTestHUD : public AHUD
{
	GENERATED_BODY()

public:

	/** 当游戏结束是点击OK时调用，而highscore名称提示符处于活动状态 */
	UPROPERTY(BlueprintAssignable)
		FOnHighscoreNameAccepted OnHighscoreNameAccepted;
	
};
