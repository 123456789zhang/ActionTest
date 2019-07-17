// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActionTestCharacter.generated.h"

UCLASS()
class ACTIONTEST_API AActionTestCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:

	/** 玩家单位的初始化 */
	virtual void PostInitializeComponents() override;

	/** 每一帧进行位置调整 */
	virtual void Tick(float DeltaSeconds) override;

	/** 设置输入绑定 */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** 使用过去的跳跃功能;重写以处理附加的跳转输入功能 */
	virtual void CheckJumpInput(float DeltaTime) override;

	/** 跑步时遇到障碍物时，从运动中得到通知 */
	virtual void MoveBlockedBy(const FHitResult& Impact) override;

	/** 如果游戏已经在半空中结束，就结束一轮 */
	virtual void Landed(const FHitResult& Hit) override;

	/** 尝试播放随机的结束动画 */
	void OnRoundFinished();

	/** 停止任何活动动画，重置移动状态 */
	void OnRoundReset();

	/** 当前玩家滑动时返回true;用于AnimBlueprint */
	UFUNCTION(BlueprintCallable, Category = "Pawn|Character")
		bool IsSliding() const;

	/** 得到bPressedSlide的值 */
	bool WantsToSlide() const;

	/** 得到CameraHeightChangeThreshold值 */
	float GetCameraHeightChangeThreshold() const;

private:

	/** 当玩家按下跳转按钮时调用的事件 */
	void OnStartJump();

	/** 当玩家释放跳转按钮时调用的事件 */
	void OnStopJump();

	/** 当玩家按下滑动按钮时调用的事件 */
	void OnStartSlide();

	/** 当玩家释放滑动按钮时调用的事件 */
	void OnStopSlide();

	/** 确定障碍高度类型并播放动画 */
	void ClimbOverObstacle();

	/** 播放随机结束动画 */
	void PlayRoundFinished();

private:

	/**
	 *相机固定在地面上，即使是在玩家跳跃的时候。
	 *但是，如果玩家跳得超过这个阈值，摄像机就会开始跟随。
	 */
	UPROPERTY(EditDefaultsOnly, Category = Config)
		float CameraHeightChangeThreshold;

	/** 玩家最小速度播放碰墙动画 */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
		float MinSpeedForHittingWall;

	/** 遇到障碍物时的动画 */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
		UAnimMontage* HitWallMontage;

	/** 攀爬器(或者准确地说是它的网格组件——可移动的部分) */
	UPROPERTY()
		UStaticMeshComponent* ClimbToMarker;

	/** 当玩家按住滑动按钮时为真 */
	uint32 bPressedSlide : 1;

	/** 我们正在攀登的攀登标志位置 */
	FVector ClimbToMarkerLoaction;

	/** 网格平移用于位置调整 */
	FVector AnimPositionAdjustment;

	/** 为攀登障碍计时器的有效管理处理 */
	FTimerHandle TimerHandle_ClimbOverObstacle;
};
