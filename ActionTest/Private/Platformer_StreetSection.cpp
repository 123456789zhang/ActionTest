// Fill out your copyright notice in the Description page of Project Settings.

#include "Platformer_StreetSection.h"
#include "ActionTestBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "ActionTestPlayerCameraManager.h"
#include "GameFramework/SaveGame.h"
#include "ActionTestSaveGame.h"
#include "UObject/UObjectGlobals.h"

APlatformer_StreetSection::APlatformer_StreetSection()
{


}

void APlatformer_StreetSection::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 10; i++)
	{
		Names.Add(FString("PCF"));
		Times.Add(FMath::FRandRange(39.0f, 50.0f));
	}

	TArray<FString> NamesTemp;

	TArray<float> TimesTemp;

	UActionTestBlueprintLibrary::SortHighscores(Times, Names, TimesTemp, NamesTemp, 10);

	Times = TimesTemp;

	Names = NamesTemp;

	RemoteEvent(FName("LoadSection_1"));

	//开始脚本
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	PlayerPawn->SetActorHiddenInGame(true);

	//设置相机
	AActionTestPlayerCameraManager* Camera =Cast<AActionTestPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(this, 0));
	Camera->SetCameraZoom(0.53f);
	Camera->SetFixedCameraOffsetZ(350.0f);


	//加载savegame或创建一个新的
	Save = Cast<UActionTestSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("PlatformerSave"), 0));

	if (Save == nullptr)
	{
		Save = Cast<UActionTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UActionTestSaveGame::StaticClass()));
		UpdateSaveHiscores();
		UGameplayStatics::SaveGameToSlot(Save, FString("PlatformerSave"), 0);
	}
	else
	{
		for (int i = 0; i < Times.Num(); i++)
		{
			float Time;
			FString Name;
			Save->GetData(Time,Name,i);
			Times[i] = Time;
			Names[i] = Name;
		}
		
	}
	
}

void APlatformer_StreetSection::LoadSection_1()
{
	
}

void APlatformer_StreetSection::UpdateSaveHiscores()
{
	for (int i = 0; i < Times.Num(); i++)
	{
		Save->SaveData(Times[i], Names[i],i);
	}
}
