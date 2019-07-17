// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameMenuBuilder.h"

/**
 * 
 */
class FPlaformerOptions : public FGameMenuPage
{
public:

	/** 设置玩家的控制器 */
	void MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner);

protected:

	TWeakObjectPtr<class UPlatformerGameUserSettings> UserSettings;

	/** 玩家的控制器 */
	TWeakObjectPtr<APlayerController> PCOwner;



};
