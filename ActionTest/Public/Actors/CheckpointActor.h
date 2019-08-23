// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InterfaceAPI.h"
#include "CheckpointActor.generated.h"

class UBoxComponent;

UCLASS()
class ACTIONTEST_API ACheckpointActor : public AActor , public IInterfaceAPI
{
	GENERATED_BODY()
	
public:	
	
	ACheckpointActor();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void SetRecord(float Time, FString Name, int32 index) override;

	UFUNCTION()
	virtual	void GetRecord(float& Time, FString& Name, int32 index) override;

	UFUNCTION()
	virtual const float GetCurrentTime() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	float DeltaTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
	bool bIsItTheLastCheckPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
	int32 CheckPointID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	bool bWinner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
	bool bStartEnding;

};
