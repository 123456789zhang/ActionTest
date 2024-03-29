// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ActionTestPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API AActionTestPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	AActionTestPlayerCameraManager();

	/** 设置CurrentZoomAlpha的新值< 0,1 > */
	UFUNCTION(BlueprintCallable, Category = "Game|Player")
		void SetCameraZoom(float ZoomAlpha);

	/** 获取当前CurrentZoomAlpha的值 */
	UFUNCTION(BlueprintCallable,Category = "Game|Player")
		float GetCameraZoom() const;

	/** 设置FixedCameraOffsetZ的新值 */
	UFUNCTION(BlueprintCallable, Category = "Game|Player")
		void SetFixedCameraOffsetZ(float InOffset);

protected:

	/** 处理相机更新 */
	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;

	/** 计算相机Z轴偏移依赖于玩家pawn的移动 */
	float CalcCameraOffsetZ(float DeltaTime);

private:

	/** 固定最大相机距离玩家pawn;用于放大 */
	FVector MaxCameraZoomOffset;

	/** 固定最小的相机距离玩家pawn;用于放大 */
	FVector MinCameraZoomOffset;

	/** 固定旋转的相机相对于玩家pawn */
	FRotator CameraFixedRotation;

	/** 变焦值< 0,1 >(0表示使用MinCameraZoomOffset, 1表示使用MaxCameraZoomOffset) */
	float CurrentZoomAlpha;

	/** 改变相机Z轴偏移的插值速度 */
	float CameraOffsetInterpSpeed;

	/** 固定相机Z轴偏移从玩家pawn */
	float FixedCameraOffsetZ;

	/** 目前使用的相机Z轴偏移 */
	float CurrentCameraOffsetZ;

	/** Z轴偏移相机应达到的目的 */
	float DesiredCameraOffsetZ;
	
};
