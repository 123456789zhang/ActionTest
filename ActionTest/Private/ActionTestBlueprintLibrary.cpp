// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestBlueprintLibrary.h"

UActionTestBlueprintLibrary::UActionTestBlueprintLibrary()
{
}

void UActionTestBlueprintLibrary::SortHighscores(TArray<float> InTimes, TArray<FString> InNames, TArray<float>& OutTimes, TArray<FString>& OutNames, int32 MaxScores)
{
	//首先排序时间和玩家名称
	for (auto iOuter = 0; iOuter < InTimes.Num(); iOuter++)
	{
		for (auto iInner = iOuter; iInner < InTimes.Num(); iInner++)
		{
			if (InTimes[iOuter] > InTimes[iInner])
			{
				InTimes.Swap(iOuter, iInner);
				InNames.Swap(iOuter, iInner);
			}
		}
	}

	//复制已排序的数组并限制大小
	OutTimes = MoveTemp(InTimes);
	OutNames = MoveTemp(InNames);

	OutTimes.RemoveAt(MaxScores, OutTimes.Num() - MaxScores);
	OutNames.RemoveAt(MaxScores, OutNames.Num() - MaxScores);
}
