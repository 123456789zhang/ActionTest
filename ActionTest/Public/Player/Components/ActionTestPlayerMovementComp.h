// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActionTestPlayerMovementComp.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API UActionTestPlayerMovementComp : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UActionTestPlayerMovementComp();

	/** 当玩家滑动时返回true */
	bool IsSliding() const;

	/** 尝试结束滑动 */
	void TryToEndSlide();

	/** 停止移动和保存当前速度与窗台抓斗修改器 */
	void PauseMovementForLedgeGrab();

	/** 设置最小滑动速度 */
	void SetMinSlideSpeed(float minSlideSpeed);

	/** 设置滑动时玩家的高度 */
	void SetSlideHeight(float slideHeight);

public:

	UPROPERTY(EditDefaultsOnly,Category = Config)
	float MaxSlideSpeed;

	/** 玩家最小速度可以滑动 */
	UPROPERTY(EditDefaultsOnly, Category = Config)
		float MinSlideSpeed;

	/** 滑动时玩家的高度 */
	UPROPERTY(EditDefaultsOnly, Category = Config)
		float SlideHeight;

	/** 在滑行过程中降低速度的值 */
	UPROPERTY(EditDefaultsOnly, Category = Config)
		float SlideVelocityReduction;

	/** 遇到障碍物后的速度倍增器 */
	UPROPERTY(EditDefaultsOnly, Category = Config)
		float ModSpeedObstacleHit;

protected:

	/** 变更滑动 */
	virtual void PhysWalking(float deltaTime, int32 Iterations) override;

	/** 自动移动 */
	virtual FVector ScaleInputAcceleration(const FVector& InputAcceleration) const override;

	/** 开始滑动 */
	void StartSlide();

	/** 改变滑动时玩家的高度调整玩家碰撞 */
	void SetSlideCollisionHeight();

	/**
	 *	将滑动后的棋子高度恢复为默认值，如果棋子上方的碰撞允许的话
	 *	如果高度更改成功，返回true，否则返回false
	 */
	bool RestoreCollisionHeightAfterSlide();

	/** 当玩家在滑动时，计算当前滑动减少的新值 */
	void CalcCurrentSlideVelocityReduction(float DeltaTime);

	/** 计算出滑动的速度，这是滑动的新速度 */
	void CalcSlideVelocity(FVector& OutVelocity) const;
	
private:

	/** 当玩家按下滑动按钮是为true */
	uint32 bInSlide:1;

	/** 保存修改后的速度值，动画完成后恢复 */
	float SavedSpeed;

	/** 当前降低滑动玩家速度的值 */
	float CurrentSlideVelocityReduction;

	/** 如果当玩家需要在滑动时使用SlideMeshRelativeLocationOffset，则为真 */
	uint32 bWantsSlideMeshRelativeLocationOffset : 1;

	/** 偏移量，当玩家滑动时，需要改变典当网格的相对位置 */
	FVector SlideMeshRelativeLocationOffset;
	
};
