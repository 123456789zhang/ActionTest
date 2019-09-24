// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ActionTestHUD.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHighscoreNameAccepted, const FString&, NewHighscoreName);


struct FActionTestMessageData
{
	/** 消息的显示 */
	FString Message;

	/** 这个FMessageData将显示多长时间(以秒为单位) */
	float DisplayDuration;

	/** 这个FMessageData首次显示是的时间秒 */
	float DisplayStartTime;

	/** x轴在屏幕上的位置< 0,1 >(0表示屏幕左侧);文本将居中 */
	float PosX;

	/** y轴在屏幕上的位置< 0,1 >(0表示屏幕顶部);文本将居中 */
	float PosY;

	/** 字体的比例 */
	float TextScale;

	/** 如果应该绘制红色边框而不是蓝色 */
	bool bRedBorder;
};

struct FBorderTextures
{
	/** 边框纹理 */
	UTexture2D* Border;

	/** 边框背景纹理 */
	UTexture2D* Background;

	/** 左边框纹理 */
	UTexture2D* LeftBorder;

	/** 右边框纹理 */
	UTexture2D* RightBorder;

	/** 上边框纹理 */
	UTexture2D* TopBorder;

	/** 下边框纹理 */
	UTexture2D* BottomBorder;
};


/**
 * 
 */
UCLASS()
class ACTIONTEST_API AActionTestHUD : public AHUD
{
	GENERATED_BODY()

public:

	/** 当游戏结束是点击OK时调用，而highscore名称提示符处于活动状态 */
	UPROPERTY(BlueprintAssignable)
		FOnHighscoreNameAccepted OnHighscoreNameAccepted;

private:

	/** 当前UI的比例 */
	float UIScale;

	/** 应该在屏幕上显示固定时间的消息数组 */
	TArray<struct FActionTestMessageData> ActiveMessage;

	/** 摘要信息 */
	TArray<struct FActionTestMessageData> EndingMessage;

	/** 是否显示高分榜 */
	uint32 bHighscoreActive : 1;

	/** 上键按钮的纹理 */
	UTexture2D* UpButtonTexture;

	/** 下键按钮的纹理 */
	UTexture2D* DownButtonTexture;

	/** HUD的字体 */
	UFont* HUDFont;

	/** 蓝色主题边框纹理 */
	FBorderTextures BlueBorder;

	/** 红色主题边框纹理 */
	FBorderTextures RedBorder;

	/** 当前高分的名字 */
	TArray<char> HighScoreName;

	/** 高分榜的名字集合 */
	TArray<FString> HighscoreNames;

	/** 高分榜的时间集合 */
	TArray<float> HighscoreTimes;

	/** 当前字母更改，同时输入高分名称 */
	uint8 CurrentLetter;

	/** 是否显示enter提示符 */
	uint32 bEnterNamePromptActive : 1;
	
	/** 修改当前时间 */
	float RoundTimeModification;

	float RoundTimeModificationTime;

public:

	AActionTestHUD();

	/** 主HUD循环更新 */
	virtual void DrawHUD() override;

	/** 设置数据并显示高分 */
	void ShowHighscore(TArray<float> Times, TArray<FString> Names);

	/** 隐藏积分榜 */
	void HideHighscore();

	/** 显示highscore提示符，当用户完成时调用HighscoreNameAccepted blueprint可实现事件 */
	void ShowHighscorePrompt();

	/** 用于向ActiveMessages数组添加新消息 */
	void AddMessage(FString Message, float DisplayDuration, float PosX, float PosY, float TextScale, bool bRedBorder);

	/** 当点击一个点击框时调用。提供与该框关联的名称。 */
	virtual void NotifyHitBoxClick(FName BoxName) override;

	/** 通知更改当前游戏的时间分数 */
	void NotifyRoundTimeModified(float DeltaTime);

protected:

	/** 用于显示活动消息和删除过期消息 */
	void DrawActiveMessages();

	/** 显示减少时间 */
	void DisplayRoundTimeModification();

	/** 用于显示具有指定参数的单个文本消息 */
	void DrawMessage(FString Message, float PosX, float PosY, float TextScale, FLinearColor TextColor, bool bRedBorder = false);
	
	/** 用平铺背景绘制3x3边框 */
	void DrawBorder(float PosX, float PosY, float Width, float Height, float BorderScale, FBorderTextures& BorderTextures);

	/** 用于显示主游戏定时器-屏幕顶部中间 */
	void DisplayRoundTimer();

	/** 绘制高分的entry提示符 */
	void DrawHighscoreEntryPrompt();

	/** 绘制高分排行榜 */
	void DrawHighscore();
};
