// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ActionTestClimbMarker.h"
#include "Components/TimelineComponent.h"
#include "Elevator2Actor.generated.h"


class UArrowComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UAudioComponent;
/**
 * 
 */
UCLASS()
class ACTIONTEST_API AElevator2Actor : public AActionTestClimbMarker
{
	GENERATED_BODY()

public:

	AElevator2Actor();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void TimelineCallback_Elevator();

	UFUNCTION()
	void TimelineFinishedCallback_StartPlaySound();

	UFUNCTION()
	void TimelineFinishedCallback_StopPlaySound();

	UFUNCTION()
	void TimelineFinishedCallback_TimelineOneReverse();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		float Current_position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		float Diff;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		float high_position;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		float low_position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		float Start_position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		float TriggerOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		bool bDirection;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Default)
		UArrowComponent* Elev;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Default)
		UStaticMeshComponent* StaticMesh1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Default)
		UStaticMeshComponent* StaticMesh2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Default)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Default)
		UAudioComponent* SoundStop;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Default)
		UAudioComponent* SoundStart;

	UPROPERTY()
		UTimelineComponent* TimelineComponentOne;

	UPROPERTY()
		UTimelineComponent* TimelineComponentTwo;

	UPROPERTY()
		UTimelineComponent* TimelineComponentThree;

	UPROPERTY()
		UTimelineComponent* TimelineComponentFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		UCurveFloat* CurveOne;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> OneTimelineDirection;

private:

	UPROPERTY()
		bool bTempOnce;
};
