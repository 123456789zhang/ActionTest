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
