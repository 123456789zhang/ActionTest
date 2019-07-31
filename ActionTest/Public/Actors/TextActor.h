// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* TimelineComponentOne;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* TimelineComponentTwo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		 UCurveFloat* FloatCurveOne;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		 UCurveFloat* FloatCurveTow;

	UPROPERTY(EditAnywhere)
		FVector Scale;

	UPROPERTY(EditAnywhere)
		FString TextToPrint;

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
