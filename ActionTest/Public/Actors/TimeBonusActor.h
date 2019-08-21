// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeBonusActor.generated.h"

class UArrowComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystemComponent;
class UTimelineComponent;

UCLASS()
class ACTIONTEST_API ATimeBonusActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATimeBonusActor();

	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform & Transform) override;

protected:
	
	virtual void BeginPlay() override;

private:

	void BounMeshRotator();

	UFUNCTION()
		void TiggerComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OneTimelineCallback(float val);

	UFUNCTION()
		void TwoTimelineCallback(float val);

	UFUNCTION()
		void OneTimelineFinishedCallback();

	UFUNCTION()
		void TwoTimelineFinishedCallback();

	UFUNCTION()
		void ShowFunction();

	UFUNCTION()
		void HiddenTextPlane();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* TextPlane;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* BonusMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		UBoxComponent* Trigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		UParticleSystemComponent* Fx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		FVector TextPlaneLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		FVector TextPlaneScale;

	UPROPERTY()
		UTimelineComponent* TimelineOne;

	UPROPERTY()
		UTimelineComponent* TimelineTwo;

	UPROPERTY(EditAnywhere,Category = Default)
		UCurveFloat* CurveOne;

	UPROPERTY(EditAnywhere, Category = Default)
		UCurveFloat* CurveTwo;

	UPROPERTY()
		float CurveFloatValueOne;

	UPROPERTY()
		float CurveFloatValueTwo;

private:

	FTimerHandle TimerHandle_BounMeshRotator;

	FTimerHandle TimerHandle_HiddenTextPlane;

};
