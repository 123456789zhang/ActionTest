// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ActionTestClimbMarker.h"
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		UArrowComponent* Elev;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		UStaticMeshComponent* StaticMesh1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		UStaticMeshComponent* StaticMesh2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		UBoxComponent* Trigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		UAudioComponent* SoundStop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Default)
		UAudioComponent* SoundStart;
};
