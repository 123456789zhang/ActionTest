// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameMenuBuilder.h"

/**
*	选择关卡
*/
class  FPlatformLevelSelect : public FGameMenuPage
{

public:

	void MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner);

protected:

	/** 开始游戏 */
	void OnUIPlayStreets();

	/** 返回主菜单 */
	void GoBack();

	/** 隐藏菜单的事件 */
	void OnMenuHiddenn();

	/** 显示加载屏幕 */
	void ShowLoadingScreen();

protected:

	/** 玩家控制器 */
	TWeakObjectPtr<APlayerController> PCOwner;
	
};
