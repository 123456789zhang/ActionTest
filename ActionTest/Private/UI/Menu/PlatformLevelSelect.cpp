// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformLevelSelect.h"
#include "Engine/Engine.h"
#include "ActionTestLoadingScreen/Public/ActionTestLoadingScreen.h"

#define LOCTEXT_NAMESPACE "PlatformerGame.HUD.Menu"
void FPlatformLevelSelect::MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner)
{
	PCOwner = _PCOwner;
	MenuTitle = LOCTEXT("LevelSelect", "关卡选择");
	AddMenuItem(LOCTEXT("Streets", "街道"), this, &FPlatformLevelSelect::OnUIPlayStreets);
	AddMenuItem(LOCTEXT("Back", "返回"), this, &FPlatformLevelSelect::GoBack);
}

void FPlatformLevelSelect::OnUIPlayStreets()
{
	if (GEngine)
	{
		SetOnHiddenHandler<FPlatformLevelSelect>(this, &FPlatformLevelSelect::OnMenuHiddenn);
		HideMenu();
	}
}

void FPlatformLevelSelect::GoBack()
{
	RootMenuPageWidget->MenuGoBack(false);
}

void FPlatformLevelSelect::OnMenuHiddenn()
{
	DestroyRootMenu();
	GEngine->SetClientTravel(PCOwner->GetWorld(), TEXT("/Game/Maps/Platformer_StreetSection"), TRAVEL_Absolute);

	PCOwner->SetInputMode(FInputModeGameOnly());
	PCOwner->bShowMouseCursor = false;

	FSlateApplication::Get().SetAllUserFocusToGameViewport();

	ShowLoadingScreen();
}

void FPlatformLevelSelect::ShowLoadingScreen()
{
	IActionTestLoadingScreenModule* LoadingScreenModule = FModuleManager::LoadModulePtr<IActionTestLoadingScreenModule>("ActionTestLoadingScreen");
	if (LoadingScreenModule != NULL)
	{
		LoadingScreenModule->StartInGameLoadingScreen();
	}
}

#undef LOCTEXT_NAMESPACE