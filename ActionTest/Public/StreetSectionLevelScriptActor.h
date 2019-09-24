// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Components/TimelineComponent.h"
#include "StreetSectionLevelScriptActor.generated.h"


class UActionTestSaveGame;
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

	virtual void Tick(float DeltaTime)override;

	UFUNCTION()
	void OnHighscoreNameAccepted(const FString& NewHighscoreName);

	UFUNCTION(BlueprintNativeEvent)
	void OnRoundFinished();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowHiscoresAndSave();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> Names;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> Times;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UActionTestSaveGame* Save;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CurrentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Hidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bWinner;

	UPROPERTY()
		class UCurveFloat* FloatCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UTimelineComponent* TimelineComponent;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY()
		float CurveFloat;
private:

	FTimerHandle TimerHandle_BindingMethod;

protected:

	UFUNCTION(BlueprintCallable)
		void UpdateSaveHiscores();

	UFUNCTION(BlueprintNativeEvent)
		void TimelineCallback(float val);

	UFUNCTION()
		void TimelineFinishedCallback();

private:

	UFUNCTION()
	void BindingMethod();

	template<typename T>
	void SetArrayElem(TArray<T>& Array, int32 index, T Item);

};

template<typename T>
void AStreetSectionLevelScriptActor::SetArrayElem(TArray<T>& Array, int32 index, T Item)
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
