// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestSaveGame.h"

UActionTestSaveGame::UActionTestSaveGame()
{
}

void UActionTestSaveGame::SaveData(float Time, FString Name, int32 index)
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

void UActionTestSaveGame::GetData(float & Time, FString & Name, int32 index)
{
	if (Records.IsValidIndex(index) && Names.IsValidIndex(index))
	{
		Time = Records[index];
		Name = Names[index];
	}
}
