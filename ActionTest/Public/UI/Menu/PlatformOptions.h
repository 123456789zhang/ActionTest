// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameMenuBuilder.h"

/** 支持分辨率的数量 */
const int32 PlatformerResCount = 4;

/** 分辨率大小 */
const FIntPoint PlatformerResolutions[PlatformerResCount] = { FIntPoint(800,600),FIntPoint(1024,768),FIntPoint(1280,720),FIntPoint(1920,1080) };
/**
*	菜单选项
*/
class  FPlatformOptions : public FGameMenuPage
{

public:

	/** 构建菜单 */
	void MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner);

	/** 在游戏设置中应用更改 */
	void ApplySettings();

	/** 返回并取消 */
	void DiscardSettings();

	/** 获取要显示的当前的值 */
	void UpdateOptions();

	/** 恢复游戏设置中未保存的更改 */
	void RevertChanges();

protected:

	/** 玩家控制器 */
	TWeakObjectPtr<APlayerController> PCOwner;

	/** 游戏的设置类 */
	TWeakObjectPtr<class UPlatformerGameUser> UserSettings;

	/** 保存音量菜单项 */
	TSharedPtr<FGameMenuItem> SoundVolumeOption;

	/** 分辨率的菜单项 */
	TSharedPtr<FGameMenuItem> VideoResolutionOption;

	/** 是否全屏的菜单项 */
	TSharedPtr<FGameMenuItem> FullScreenOption;

	/** 选项菜单的音量大小 */
	float SoundVolumeOpt;

	/** 设置菜单的分辨率选项的值 */
	FIntPoint ResolutionOpt;

	/** 设置菜单的全屏选项的值 */
	EWindowMode::Type bFullScreenOpt;
	  
protected:

	/** 音量触发的事件 */
	void SoundVolumeOptionChanged(TSharedPtr<FGameMenuItem> MenuItem,int32 MultiOptionIndex);
	
	/** 分辨率的触发事件 */
	void VideoResolutionOptionChanged(TSharedPtr<FGameMenuItem> MenuItem, int32 MultiOptionIndex);

	/** 是否全屏的触发事件 */
	void FullScreenOptionChanged(TSharedPtr<FGameMenuItem> MenuItem, int32 MultiOptionIndex);

	/** 应用按钮触发的事件 */
	void OnAcceptSettings();

	/** 取消按钮触发的事件 */
	void OnDiscardSettings();

	/** 尝试将当前分辨率与所选索引匹配 */
	int32 GetCurrentResolutionIndex(FIntPoint CUrrentRes);
	
};
