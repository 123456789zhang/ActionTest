// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "StreetSectionLevelScriptActor.generated.h"


class USaveGame;
/**
 * 
 */
UCLASS()
class ACTIONTEST_API AStreetSectionLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	AStreetSectionLevelScriptActor();


	virtual void BeginPlay() override;



public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> Names;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> Times;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USaveGame* Save;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CurrentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentTiem;

protected:

	UFUNCTION(BlueprintCallable)
		void UpdateSaveHiscores();

private:

	template<typename T>
	void SetArrayElem(TArray<T> Array, int32 index, T Item);

};

template<typename T>
void AStreetSectionLevelScriptActor::SetArrayElem(TArray<T> Array, int32 index, T Item)
{
	if (!Array.IsValidIndex(index))
	{
		Array.SetNum(index + 1);
	}
	if (Array.IsValidIndex(index))
	{
		Array[index] = Item;
	}
}