// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeBonusActor.generated.h"

class UArrowComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONTEST_API ATimeBonusActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATimeBonusActor();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* TextPlane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UStaticMeshComponent* BonusMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		UParticleSystemComponent* Fx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		FVector TextPlaneLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		FVector TextPlaneScale;

};
