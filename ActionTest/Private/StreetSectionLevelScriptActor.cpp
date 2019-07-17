// Fill out your copyright notice in the Description page of Project Settings.

#include "StreetSectionLevelScriptActor.h"
#include "ActionTestBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ActionTestSaveGame.h"

AStreetSectionLevelScriptActor::AStreetSectionLevelScriptActor()
{
}


void AStreetSectionLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 10; i++)
	{
		Names.Add(TEXT("PCF"));
		Times.Add(FMath::FRandRange(39, 50));
	}

	UActionTestBlueprintLibrary::SortHighscores(Names, Times, Times, Names, 10);

	Save = UGameplayStatics::LoadGameFromSlot(FString(TEXT("PlatformerSave")),0);

	if (Save == nullptr)
	{
		Save = UGameplayStatics::CreateSaveGameObject(UActionTestSaveGame::StaticClass());

		UpdateSaveHiscores();

		UGameplayStatics::SaveGameToSlot(Save, FString(TEXT("PlatformerSave")),0);
	}
	else 
	{
		UActionTestSaveGame* ActionTestSave = Cast<UActionTestSaveGame>(Save);
		for (int i = 0; i < ActionTestSave->Records.Num(); i++)
		{
			float Time;
			FString Name;
			ActionTestSave->GetRecord(Time, Name, i);
			SetArrayElem<float>(Times, i, Time);
			SetArrayElem<FString>(Names, i, Name);
		}
	}
}

void AStreetSectionLevelScriptActor::UpdateSaveHiscores()
{
	for (int i = 0; i < Times.Num(); i++)
	{
		UActionTestSaveGame* ActionTestSave = Cast<UActionTestSaveGame>(Save);
		ActionTestSave->SetRecord(Times[i],Names[i],i);
	}
}


