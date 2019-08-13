// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DYnamicRamp2Actor.generated.h"

class UArrowComponent;
class UBoxComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;

UCLASS()
class ACTIONTEST_API ADYnamicRamp2Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ADYnamicRamp2Actor();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	void FlatFalling();

	void ResetPivot();

	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UArrowComponent* Pirvot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UBoxComponent* Box1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UParticleSystemComponent* Explosion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* StaticMesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* StaticMesh2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* StaticMesh3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* StaticMesh4;

	UPROPERTY(EditAnywhere, Category = Default)
		UCurveFloat* FloatCurve;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY()
		UTimelineComponent* Timeline;

private:

	UPROPERTY()
		bool bIsBranch;

	UPROPERTY()
		float CurveFloatValue;

	FTimerHandle TimeHanlde_FlatFalling;

	FTimerHandle TimeHanlde_ResetPivot;

};
