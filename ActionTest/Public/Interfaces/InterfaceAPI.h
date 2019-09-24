// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceAPI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UInterfaceAPI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONTEST_API IInterfaceAPI
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual	void SetRecord(float Time, FString Name, int32 index) = 0;

	UFUNCTION(BlueprintCallable)
	virtual	void GetRecord(float& Time, FString& Name, int32 index) = 0;

	UFUNCTION(BlueprintCallable)
	virtual const float GetCurrentTime() = 0;

};
