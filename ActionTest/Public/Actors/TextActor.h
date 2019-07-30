// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextActor.generated.h"

class UArrowComponent;
class UBoxComponent;
class UTextRenderComponent;

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

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);





};
