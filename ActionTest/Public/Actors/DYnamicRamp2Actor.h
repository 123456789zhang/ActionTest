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

public:	
	
	virtual void Tick(float DeltaTime) override;

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

};
