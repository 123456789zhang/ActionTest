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
	UWorld* const MyWorld = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::Assert);
	AActionTestGameMode* const MyGameMode = MyWorld->GetAuthGameMode<AActionTestGameMode>();
	if (MyGameMode && MyGameMode->ActionTestPicture)
	{
		MyGameMode->ActionTestPicture->Hide(FadeOutTime);
	}
}

void UActionTestBlueprintLibrary::ShowHighscore(UObject * WorldContextObject, TArray<float> Times, TArray<FString> Names)
{
	APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert));
	AActionTestHUD* MyHUD = LocalPC ? Cast<AActionTestHUD>(LocalPC->GetHUD()) : NULL;
	if (MyHUD)
	{
		MyHUD->ShowHighscore(Times,Names);
	}
}

void UActionTestBlueprintLibrary::HideHighscore(UObject * WorldContextObject)
{
	APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert));
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

void UActionTestBlueprintLibrary::DecreaseRoundDuration(UObject * WorldContextObject, float DeltaTime)
{
	AActionTestGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		const float Delta = FMath::Abs(DeltaTime);
		MyGame->ModifyRoundDuration(Delta, (DeltaTime > 0) ? false : true);
	}
}

float UActionTestBlueprintLibrary::GetCurrentCheckpointTime(UObject * WorldContextObject, int32 CheckpointID)
{
	AActionTestGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		return MyGame->GetCurrentCheckpointTime(CheckpointID);
	}
	return -1.0f;
}

float UActionTestBlueprintLibrary::MarkCheckpointTime(UObject * WorldContextObject, int32 CheckpointID)
{
	float DeltaTime = 0.0f;
	AActionTestGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		const float PrevBastTime = MyGame->GetBastCheckpointTime(CheckpointID);

		MyGame->SaveCheckpointTime(CheckpointID);

		if (PrevBastTime > 0)
		{
			const float CurrentTime = MyGame->GetCurrentCheckpointTime(CheckpointID);
			DeltaTime = CurrentTime - PrevBastTime;
		}
	}

	return DeltaTime;
}

bool UActionTestBlueprintLibrary::FinishRace(UObject * WorldContextObject)
{
	bool bHasWon = false;

	AActionTestGameMode* MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->FinishRound();
		bHasWon = MyGame->IsRoundWon();
	}

	return bHasWon;
}

FString UActionTestBlueprintLibrary::DescribeTime(float TimeSeconds, bool bShowSign)
{
	const float AbsTimeSeconds = FMath::Abs(TimeSeconds);
	const bool bIsNegative = (TimeSeconds < 0);

	const int32 TotalSeconds = FMath::TruncToInt(AbsTimeSeconds) % 3600;
	const int32 NumMinutes = TotalSeconds / 60;
	const int32 NumSeconds = TotalSeconds % 60;
	
	const int32 NUmMiliSeconds = FMath::TruncToInt(FMath::Fractional(AbsTimeSeconds) * 1000.0f);

	FString TimeDesc = FString::Printf(TEXT("%s%02d:%02d.%03d"),
		bShowSign ? (bIsNegative ? TEXT("-") : TEXT("+")) : TEXT(""),
		NumMinutes, NumSeconds, NUmMiliSeconds);

	return TimeDesc;
}

void UActionTestBlueprintLibrary::DisplayMessage(UObject * WorldContextObject, FString Message, float DisplayDuration, float PosX, float PosY, float TextScale, bool bRedBorder)
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
