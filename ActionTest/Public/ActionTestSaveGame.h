// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ActionTestSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API UActionTestSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UActionTestSaveGame();

	void SaveData(float Time, FString Name, int32 index);

	void GetData(float& Time, FString& Name, int32 index);
	
private:

	UPROPERTY()
	TArray<float> Records;

	UPROPERTY()
	TArray<FString> Names;
};
