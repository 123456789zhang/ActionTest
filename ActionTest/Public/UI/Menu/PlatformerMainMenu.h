// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameMenuBuilder/Public/GameMenuBuilder.h"


class  FPlatformerMainMenu : public FGameMenuPage
{
	
public:

	void MakeMenu(APlayerController* InPCowner);
	void OnQuit();

};
