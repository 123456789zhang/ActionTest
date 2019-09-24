// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Interfaces/InterfaceAPI.h"
#include "ActionTestSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API UActionTestSaveGame : public USaveGame,public IInterfaceAPI
{
	GENERATED_BODY()

public:

	UActionTestSaveGame(){}

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
		TArray<float> Records;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
		TArray<FString> Names;

public:

	UFUNCTION(BlueprintCallable)
	virtual void SetRecord(float Time,FString Name,int32 index) override;

	UFUNCTION(BlueprintCallable)
	virtual void GetRecord(float& Time, FString& Name, int32 index)override;

	UFUNCTION(BlueprintCallable)
	virtual const float GetCurrentTime() override;
};
