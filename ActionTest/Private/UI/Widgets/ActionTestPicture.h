// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UCanvas;
/**
 * 
 */
class FActionTestPicture
{
public:

	FActionTestPicture(UWorld* World);
	
	/** 隐藏图片 */
	void Hide(float FadeOutTime);

	/** 检查图片当前是否可见 */
	bool IsVisible() const;

	/** 用于淡入淡出 */
	void Tick(UCanvas* Canvas);

	/** 显示图片 */
	void Show(UTexture2D* InTexture,float InFadeInTime,float InScreenCoverage,bool bInKeepAspectRatio);

protected:

	/** 如果当前正在绘制图片 */
	bool bIsVisible;

	/** 如果图像正在淡出 */
	bool bIsHiding;

	/** 淡入或淡入启动时间 */
	float AnimStartedTime;

	/** 当前动画应播放多长时间(淡入或淡出) */
	float AnimTime;

	/** 画面色彩的颜色 */
	FLinearColor TintColor;

	/** 图片比例尺与视口尺寸1.0f =全屏 */
	float ScreenCoverage;

	/** 如果图片在缩放时应保持高宽比或使用视口高宽比 */
	bool bKeepAspectRatio;

	/** 图片的指针 */
	UTexture2D* Image;

	/** 世界的指针 */
	UWorld* OwnerWorld;
};
