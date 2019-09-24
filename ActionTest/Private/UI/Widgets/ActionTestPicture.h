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
	
	/** ����ͼƬ */
	void Hide(float FadeOutTime);

	/** ���ͼƬ��ǰ�Ƿ�ɼ� */
	bool IsVisible() const;

	/** ���ڵ��뵭�� */
	void Tick(UCanvas* Canvas);

	/** ��ʾͼƬ */
	void Show(UTexture2D* InTexture,float InFadeInTime,float InScreenCoverage,bool bInKeepAspectRatio);

protected:

	/** �����ǰ���ڻ���ͼƬ */
	bool bIsVisible;

	/** ���ͼ�����ڵ��� */
	bool bIsHiding;

	/** �����������ʱ�� */
	float AnimStartedTime;

	/** ��ǰ����Ӧ���Ŷ೤ʱ��(����򵭳�) */
	float AnimTime;

	/** ����ɫ�ʵ���ɫ */
	FLinearColor TintColor;

	/** ͼƬ���������ӿڳߴ�1.0f =ȫ�� */
	float ScreenCoverage;

	/** ���ͼƬ������ʱӦ���ָ߿�Ȼ�ʹ���ӿڸ߿�� */
	bool bKeepAspectRatio;

	/** ͼƬ��ָ�� */
	UTexture2D* Image;

	/** �����ָ�� */
	UWorld* OwnerWorld;
};
