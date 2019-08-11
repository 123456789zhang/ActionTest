// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "ExplodingCarActor.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UTimelineComponent;

UCLASS()
class ACTIONTEST_API AExplodingCarActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AExplodingCarActor();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

private:

	UFUNCTION()
	void  OnColissionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void  OnCloseContactTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

	UFUNCTION()
	void LaunchCharacter();

	UFUNCTION()
	void ResetObject();

	void Gate(int32 val);

	void SequenceMethod();

public:

	/** 车模型 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* Mesh;

	/** 碰撞 */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Default)
		UBoxComponent* Box1;

	/** 碰撞 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UBoxComponent* Colission;

	/** 碰撞 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UBoxComponent* CloseContactTrigger;

	/** 粒子系统 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UParticleSystemComponent* Explosion;

	/** 引擎盖 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* Mask;

	/** 后盖 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* RoofBack;

	/** 车顶 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* RoofTop;

	/** 引擎盖旋转 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		FRotator MaskRotation;

	/** 车顶旋转 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		FRotator RoofMidRotation;

	/**后盖旋转 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		FRotator RoofBackRotation;

	/** 在汽车上着陆时的速度 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		float LaunchSpeed;

	/** 时间轴 */
	UPROPERTY(EditAnywhere, Category = Default)
		UCurveFloat* FloatCurve;

private:

	UPROPERTY()
	UTimelineComponent* TimelineComponent;

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY()
		float CurveFloatValue;

	FTimerHandle TimerHandle_LaunchCharacter;

	FTimerHandle TimerHandle_ResetObject;

	UPROPERTY()
	bool TempBool;

	UPROPERTY()
	bool TempBoolGateOpenOrClose;

};
