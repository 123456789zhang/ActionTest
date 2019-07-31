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

	UPROPERTY()
		float OneCurveFloatValue;

	UPROPERTY()
		float TwoCurveFloatValue;

	UPROPERTY(Transient)
		bool TempBool;

	UPROPERTY(Transinet)
		bool TempBoolIsClosed;

	UPROPERTY(Transinet)
		bool TempBoolGateOpenOrClose;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OneTimelineCallback();

	UFUNCTION()
	void OneTimelineFinishedCallback();

	UFUNCTION()
		void TwoTimelineCallback();

	UFUNCTION()
		void TwoTimelineFinishedCallback();

	void Gate(int32 value);

	void SequenceOne();
};
