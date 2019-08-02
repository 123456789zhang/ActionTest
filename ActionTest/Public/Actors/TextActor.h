// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "TextActor.generated.h"

class UArrowComponent;
class UBoxComponent;
class UTextRenderComponent;
class UTimelineComponent;
class UCurveFloat;

UCLASS()
class ACTIONTEST_API ATextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATextActor();
	
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(BlueprintReadOnly)
		UArrowComponent* Object;

	UPROPERTY(BlueprintReadOnly)
		UBoxComponent* Trigger;

	UPROPERTY(BlueprintReadOnly)
		UTextRenderComponent* Text;

	UPROPERTY()
		UTimelineComponent* TimelineComponentOne;

	UPROPERTY()
		UTimelineComponent* TimelineComponentTwo;

	UPROPERTY(EditAnywhere, Category = Default)
		 UCurveFloat* FloatCurveOne;

	UPROPERTY(EditAnywhere, Category = Default)
		 UCurveFloat* FloatCurveTow;

	UPROPERTY(EditAnywhere, Category = Default)
		FVector Scale;

	UPROPERTY(EditAnywhere, Category = Default)
		FString TextToPrint;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> OneTimelineDirection;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TwoTimelineDirection;

	UPROPERTY()
		float OneCurveFloatValue;

	UPROPERTY()
		float TwoCurveFloatValue;

	UPROPERTY(Transient)
	bool TempBool;

	UPROPERTY(Transient)
	bool TempBoolTwo;

	UPROPERTY(Transient)
	bool TempBoolGateOpenOrClose;

	UPROPERTY(Transient)
	bool TempBoolGateOpenOrCloseTwo;

	FTimerHandle TimeLineHandle;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OneTimelineCallback(float val);

	UFUNCTION()
	void OneTimelineFinishedCallback();

	UFUNCTION()
	void TwoTimelineCallback(float val);

	UFUNCTION()
	void TwoTimelineFinishedCallback();

	void GateOne(int32 value);

	void GateTwo(int32 value);

	void SequenceOne();

	void SequenceTwo();

	void OpenTimelineTwo();
};
