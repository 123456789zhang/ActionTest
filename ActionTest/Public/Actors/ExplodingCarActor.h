// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplodingCarActor.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONTEST_API AExplodingCarActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AExplodingCarActor();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		UBoxComponent* Box1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Colission;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* CloseContactTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UParticleSystemComponent* Explosion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mask;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* RoofBack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* RoofTop;

};
