// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionTestBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API UActionTestBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UActionTestBlueprintLibrary();

	/** 切换到等待状态，玩家可以自己开始比赛 */
	UFUNCTION(BlueprintCallable, Category = Game, meta = (WorldContext="WorldContextObject"))
		static void PrepareRace(class UObject* WorldContextObject);

	/** 隐藏之前显示的图片 */
	UFUNCTION(BlueprintCallable, Category = HUD, meta = (WorldContext = "WorldContextObject"))
		static void HidePicture(class UObject* WorldContextObject, float FadeOutTime = 0.3f);

	/** 显示提供数据的最高分数 */
	UFUNCTION(BlueprintCallable, Category = HUD, meta = (WorldContext = "WorldContextObject"))
		static void ShowHighscore(class UObject* WorldContextObject, TArray<float> Times, TArray<FString> Names);

	/** 隐藏最高分数榜 */
	UFUNCTION(BlueprintCallable, Category = HUD, meta = (WorldContext = "WorldContextObject"))
		static void HideHighscore(class UObject* WorldContextObject);

	/** 允许玩家重新开始 */
	UFUNCTION(BlueprintCallable, Category = Game, meta = (WorldContext = "WorldContextObject"))
		static void AllowToRestartRace(class UObject* WorldContextObject);

	/** 允许改变回合持续时间，而回合仍在进行中-用于给玩家时间奖励 */
	UFUNCTION(BlueprintCallable, Category = Game, meta = (WorldContext = "WorldContextObject"))
		static void DecreaseRoundDuration(class UObject* WorldContextObject, float DeltaTime);

	/** 返回当前轮中保存的检查点时间 */
	UFUNCTION(BlueprintCallable, Category = Game, meta = (WorldContext = "WorldContextObject"))
		static float GetCurrentCheckpointTime(class UObject* WorldContextObject, int32 CheckpointID);

	/** 返回当前检查点时间与最佳时间之间的增量(负=较好时间) */
	UFUNCTION(BlueprintCallable, Category = Game, meta = (WorldContext = "WorldContextObject"))
		static float MarkCheckpointTime(class UObject* WorldContextObject, int32 CheckpointID);

	/** 完成一轮后，玩家将能够重播，得分时返回true */
	UFUNCTION(BlueprintCallable, Category = Game, meta = (WorldContext = "WorldContextObject"))
		static bool FinishRace(class UObject* WorldContextObject);

	/** 将时间转换为字符串，单位为mm:ss.sss格式 */
	UFUNCTION(BlueprintPure, Category = HUD)
		static FString DescribeTime(float TimeSeconds,bool bShowSign);

	/** 显示信息 */
	UFUNCTION(BlueprintCallable, Category = HUD, meta = (WorldContext = "WorldContextObject"))
		static void DisplayMessage(class UObject* WorldContextObject, FString Message, float DisplayDuration = 1.0f, float PosX = 0.5f, float PosY = 0.5f, float TextScale = 1.0f, bool bRedBorder = false);

	/* 
	 *	分数排序
	 *
	 * @param	InTimes		输入的分数
	 * @param	InNames		输入的玩家名称
	 * @param	OutTimes	输出的分数
	 * @param	OutNames	输出的玩家名称
	 * @param	MaxScores	将输出时间限制在这个范围内
	 */
	UFUNCTION(BlueprintCallable, Category = Game)
	static void SortHighscores(TArray<float> InTimes, TArray<FString> InNames, TArray<float>& OutTimes, TArray<FString>& OutNames, int32 MaxScores);
};
