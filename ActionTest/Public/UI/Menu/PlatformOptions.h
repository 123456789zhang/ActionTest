// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameMenuBuilder.h"

/** ֧�ֱַ��ʵ����� */
const int32 PlatformerResCount = 4;

/** �ֱ��ʴ�С */
const FIntPoint PlatformerResolutions[PlatformerResCount] = { FIntPoint(800,600),FIntPoint(1024,768),FIntPoint(1280,720),FIntPoint(1920,1080) };
/**
*	�˵�ѡ��
*/
class  FPlatformOptions : public FGameMenuPage
{

public:

	/** �����˵� */
	void MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner);

	/** ����Ϸ������Ӧ�ø��� */
	void ApplySettings();

	/** ���ز�ȡ�� */
	void DiscardSettings();

	/** ��ȡҪ��ʾ�ĵ�ǰ��ֵ */
	void UpdateOptions();

	/** �ָ���Ϸ������δ����ĸ��� */
	void RevertChanges();

protected:

	/** ��ҿ����� */
	TWeakObjectPtr<APlayerController> PCOwner;

	/** ��Ϸ�������� */
	TWeakObjectPtr<class UPlatformerGameUser> UserSettings;

	/** ���������˵��� */
	TSharedPtr<FGameMenuItem> SoundVolumeOption;

	/** �ֱ��ʵĲ˵��� */
	TSharedPtr<FGameMenuItem> VideoResolutionOption;

	/** �Ƿ�ȫ���Ĳ˵��� */
	TSharedPtr<FGameMenuItem> FullScreenOption;

	/** ѡ��˵���������С */
	float SoundVolumeOpt;

	/** ���ò˵��ķֱ���ѡ���ֵ */
	FIntPoint ResolutionOpt;

	/** ���ò˵���ȫ��ѡ���ֵ */
	EWindowMode::Type bFullScreenOpt;
	  
protected:

	/** �����������¼� */
	void SoundVolumeOptionChanged(TSharedPtr<FGameMenuItem> MenuItem,int32 MultiOptionIndex);
	
	/** �ֱ��ʵĴ����¼� */
	void VideoResolutionOptionChanged(TSharedPtr<FGameMenuItem> MenuItem, int32 MultiOptionIndex);

	/** �Ƿ�ȫ���Ĵ����¼� */
	void FullScreenOptionChanged(TSharedPtr<FGameMenuItem> MenuItem, int32 MultiOptionIndex);

	/** Ӧ�ð�ť�������¼� */
	void OnAcceptSettings();

	/** ȡ����ť�������¼� */
	void OnDiscardSettings();

	/** ���Խ���ǰ�ֱ�������ѡ����ƥ�� */
	int32 GetCurrentResolutionIndex(FIntPoint CUrrentRes);
	
};
