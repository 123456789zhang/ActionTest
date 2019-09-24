// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZoomActor.generated.h"

class UBoxComponent;

UCLASS()
class ACTIONTEST_API AZoomActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AZoomActor();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CameraMobile();

	UFUNCTION()
	void ExecuteSwitch(int32 EntryPoint);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		float Camera_Zoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		int32 Camera_ZoomDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Default)
		float Zoom_backup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
		bool bZoomInFirst;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
		float ZoomSpeed;

private:

	UPROPERTY(EditDefaultsOnly, Category = Default)
		UBoxComponent* Box;

};
