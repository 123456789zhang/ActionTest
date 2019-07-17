// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnims.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API UPlayerAnims : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPlayerAnims();

	/** ¶¯»­µÄtickº¯Êý */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:

	UPROPERTY(BlueprintReadOnly)
		bool bInSlide;

	UPROPERTY(BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly)
		float Speed;
	
};
