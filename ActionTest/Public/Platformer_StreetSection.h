// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Platformer_StreetSection.generated.h"


class UActionTestSaveGame;
/**
 * 
 */
UCLASS()
class ACTIONTEST_API APlatformer_StreetSection : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	APlatformer_StreetSection();

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void LoadSection_1();


	UFUNCTION()
	void UpdateSaveHiscores();

private:

	//排行榜的名称
	UPROPERTY()
	TArray<FString> Names;

	//排行榜的时间
	UPROPERTY()
	TArray<float> Times;

	//游戏保存
	UPROPERTY()
	UActionTestSaveGame* Save;



	
};
