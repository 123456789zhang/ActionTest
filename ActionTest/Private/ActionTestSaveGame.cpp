// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestSaveGame.h"

void UActionTestSaveGame::SetRecord(float Time, FString Name, int32 index)
{

	if (!Records.IsValidIndex(index))
	{
		Records.SetNum(index + 1);
	}
	if (!Names.IsValidIndex(index))
	{
		Names.SetNum(index + 1);
	}

	if (Names.IsValidIndex(index) || Records.IsValidIndex(index))
	{
		Records[index] = Time;
		Names[index] = Name;
	}
}

void UActionTestSaveGame::GetRecord(float & Time, FString & Name, int32 index)
{
	Time = Records[index];
	Name = Names[index];
}
