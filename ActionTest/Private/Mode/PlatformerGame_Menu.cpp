// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerGame_Menu.h"
#include "PlatfromerPlayerController_Menu.h"



APlatformerGame_Menu::APlatformerGame_Menu(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	PlayerControllerClass = APlatfromerPlayerController_Menu::StaticClass();
}


void APlatformerGame_Menu::RestartPlayer(AController * NewPlayer)
{

}
