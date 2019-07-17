// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatfromerPlayerController_Menu.h"
#include "PlatformerMainMenu.h"

APlatfromerPlayerController_Menu::APlatfromerPlayerController_Menu(const FObjectInitializer& ObjectInitializer) 
	:Super(ObjectInitializer)
{

}

void APlatfromerPlayerController_Menu::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PlatformerMainMenu = MakeShareable(new FPlatformerMainMenu());
	PlatformerMainMenu->MakeMenu(this);
	PlatformerMainMenu->ShowRootMenu();
}

void APlatfromerPlayerController_Menu::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlatformerMainMenu.IsValid())
	{
		PlatformerMainMenu->DestroyRootMenu();
		PlatformerMainMenu = nullptr;
	}
}
