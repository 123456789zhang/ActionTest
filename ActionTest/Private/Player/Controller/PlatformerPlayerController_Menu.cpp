// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerPlayerController_Menu.h"
#include "PlatformerMainMenu.h"


APlatformerPlayerController_Menu::APlatformerPlayerController_Menu(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{

}

void APlatformerPlayerController_Menu::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlatformerMainMenu = MakeShareable(new FPlatformerMainMenu());
	PlatformerMainMenu->MakeMenu(this);
}

void APlatformerPlayerController_Menu::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}
