#pragma once

#include "ModuleInterface.h"
#include "ModuleManager.h"

class IActionTestLoadingScreenModule : public IModuleInterface
{

public:

	/** 启动游戏加载界面(非启动) */
	virtual void StartInGameLoadingScreen() = 0;
};