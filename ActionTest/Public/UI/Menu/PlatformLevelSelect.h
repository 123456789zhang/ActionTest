// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameMenuBuilder.h"

/**
*	ѡ��ؿ�
*/
class  FPlatformLevelSelect : public FGameMenuPage
{

public:

	void MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner);

protected:

	/** ��ʼ��Ϸ */
	void OnUIPlayStreets();

	/** �������˵� */
	void GoBack();

	/** ���ز˵����¼� */
	void OnMenuHiddenn();

	/** ��ʾ������Ļ */
	void ShowLoadingScreen();

protected:

	/** ��ҿ����� */
	TWeakObjectPtr<APlayerController> PCOwner;
	
};
