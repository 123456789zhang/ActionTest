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

protected:

	/** 自动移动 */
	virtual FVector ScaleInputAcceleration(const FVector& InputAcceleration) const override;
	
};
