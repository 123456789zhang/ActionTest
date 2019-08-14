// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestClimbMarker.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AActionTestClimbMarker::AActionTestClimbMarker()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ClimbMarkerOb(TEXT("/Game/Environment/meshes/ClimbMarker"));

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	RootComponent = SceneComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(ClimbMarkerOb.Object);
	Mesh->RelativeScale3D = FVector(0.25f, 1.0f, 0.25f);
	Mesh->SetupAttachment(RootComponent);
	
}


