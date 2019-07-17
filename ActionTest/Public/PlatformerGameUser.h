// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "PlatformerGameUser.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONTEST_API UPlatformerGameUser : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()


	float GetSoundVolume() const
	{
		return SoundVolume;
	}

	void SetSoundVolume(float InVolume)
	{
		SoundVolume = InVolume;
	}
	
private:

	/** “Ù¿÷“Ù¡ø */
	UPROPERTY(config)
		float  SoundVolume;
};
