 // Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformerMainMenu.h"
#include "Engine/Engine.h"
#include "PlatformLevelSelect.h"
#include "PlatformOptions.h"

#define LOCTEXT_NAMESPACE "PlatformerGame.HUD.Menu"

void FPlatformerMainMenu::MakeMenu(APlayerController * InPCowner)
{
	TSharedRef<FPlatformOptions>  Options = MakeShareable(new FPlatformOptions());
	Options->MakeMenu(InPCowner);
	Options->ApplySettings();

	TSharedRef<FPlatformLevelSelect> LevelSelect = MakeShareable(new FPlatformLevelSelect());
	LevelSelect->MakeMenu(InPCowner);

	if (InitialiseRootMenu(InPCowner, TEXT("/Game/UI/Styles/PlatformerMenuStyle"), GEngine->GameViewport) == true)
	{
		MenuTitle = LOCTEXT("MainMenu", "主菜单");

		AddMenuItem(LOCTEXT("PlayGame", "开始游戏") , LevelSelect);
		AddMenuItem(LOCTEXT("Options", "选项"), Options);
		AddMenuItem(LOCTEXT("Quit", "退出"), this, &FPlatformerMainMenu::OnQuit);
	}
}

void FPlatformerMainMenu::OnQuit()
{
	PCOwner->ConsoleCommand("quit");
}

#undef LOCTEXT_NAMESPACE
