#pragma once

#include "ModuleInterface.h"
#include "ModuleManager.h"

class IActionTestLoadingScreenModule : public IModuleInterface
{

public:

	/** ������Ϸ���ؽ���(������) */
	virtual void StartInGameLoadingScreen() = 0;
};