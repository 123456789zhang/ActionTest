// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionTestClimbMarker.generated.h"

UCLASS()
class ACTIONTEST_API AActionTestClimbMarker : public AActor
{
	GENERATED_BODY()
	
public:

	AActionTestClimbMarker();

private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;

public:

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

};
