// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerOptions.h"

void FPlaformerOptions::MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner)
{
	PCOwner = _PCOwner;

	UserSettings = NULL;

}
