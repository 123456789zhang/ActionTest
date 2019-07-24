// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionTestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API AActionTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AActionTestPlayerController();

	/** ³¢ÊÔ¿ªÊ¼ÓÎÏ· */
	bool TryStartingGame();
	
};
