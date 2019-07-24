// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestBlueprintLibrary.h"
#include "Engine/Engine.h"
#include "ActionTestGameMode.h"
#include "Private/UI/Widgets/ActionTestPicture.h"
#include "ActionTestHUD.h"

UActionTestBlueprintLibrary::UActionTestBlueprintLibrary()
{
}

AActionTestGameMode* GetGameFromContextObject(class UObject* WorldContextObject)
{
	UWorld* const MyWorld = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	check(MyWorld);

	AActionTestGameMode* const MyGame = MyWorld->GetAuthGameMode<AActionTestGameMode>();
	return MyGame;
}

void UActionTestBlueprintLibrary::PrepareRace(UObject * WorldContextObject)
{
	AActionTestGameMode* const MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->PrepareRound();
	}
}

void UActionTestBlueprintLibrary::HidePicture(UObject * WorldContextObject, float FadeOutTime)
{
	UWorld* const MyWorld = GEngine->GetWorldFromContextObject(WorldContextObject);
	AActionTestGameMode* const MyGameMode = MyWorld->GetAuthGameMode<AActionTestGameMode>();
	if (MyGameMode && MyGameMode->ActionTestPicture)
	{
		MyGameMode->ActionTestPicture->Hide(FadeOutTime);
	}
}

void UActionTestBlueprintLibrary::ShowHighscore(UObject * WorldContextObject, TArray<float> Times, TArray<FString> Names)
{
	APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(GEngine->GetWorldFromContextObject(WorldContextObject));
	AActionTestHUD* MyHUD = LocalPC ? Cast<AActionTestHUD>(LocalPC->GetHUD()) : NULL;
	if (MyHUD)
	{
		MyHUD->ShowHighscore(Times,Names);
	}
}

void UActionTestBlueprintLibrary::HideHighscore(UObject * WorldContextObject)
{
	APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(GEngine->GetWorldFromContextObject(WorldContextObject));
	AActionTestHUD* MyHUD = LocalPC ? Cast<AActionTestHUD>(LocalPC->GetHUD()) : NULL;
	if (MyHUD)
	{
		MyHUD->HideHighscore();
	}
}

void UActionTestBlueprintLibrary::AllowToRestartRace(UObject * WorldContextObject)
{
	AActionTestGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->SetCanBeRestarted(true);
	}
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
