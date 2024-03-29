// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestSaveGame.h"

void UActionTestSaveGame::SetRecord(float Time, FString Name, int32 index)
{
	if (!Records.IsValidIndex(index) && !Names.IsValidIndex(index))
	{
		Records.SetNum(index + 1);
		Names.SetNum(index + 1);
	}

	if (Records.IsValidIndex(index) && Names.IsValidIndex(index))
	{
		Records[index] = Time;
		Names[index] = Name;
	}
}

void UActionTestSaveGame::GetRecord(float & Time, FString & Name, int32 index)
{
	if (Records.IsValidIndex(index) && Names.IsValidIndex(index))
	{
		Time = Records[index];
		Name = Names[index];
	}
}

const float UActionTestSaveGame::GetCurrentTime()
{
	return 0.0f;
}
