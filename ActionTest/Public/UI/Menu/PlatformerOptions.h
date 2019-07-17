// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameMenuBuilder.h"

/**
 * 
 */
class FPlaformerOptions : public FGameMenuPage
{
public:

	/** ������ҵĿ����� */
	void MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner);

protected:

	TWeakObjectPtr<class UPlatformerGameUserSettings> UserSettings;

	/** ��ҵĿ����� */
	TWeakObjectPtr<APlayerController> PCOwner;



};
