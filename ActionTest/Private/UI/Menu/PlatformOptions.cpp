// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformOptions.h"
#include "PlatformerGameUser.h"
#include "Engine/Engine.h"
#include "PlatformerGameUser.h"

#define LOCTEXT_NAMESPACE "PlatformerGame.HUD.Menu"
void FPlatformOptions::MakeMenu(TWeakObjectPtr<APlayerController> _PCOwner)
{
	PCOwner = _PCOwner;
	UserSettings = NULL;

	TArray<FText> ResolutionList;  //分辨率的集合
	TArray<FText> OnOffList;//是否全屏
	TArray<FText> VolumeList;//音量的集合

	//赋值分辨率
	for (int32 i = 0; i < PlatformerResCount; i++)
	{
		ResolutionList.Add(FText::Format(FText::FromString("{0}x{1}"), FText::AsNumber(PlatformerResolutions[i].X), FText::AsNumber(PlatformerResolutions[i].Y)));
	}

	OnOffList.Add(LOCTEXT("Off","OFF"));
	OnOffList.Add(LOCTEXT("On", "ON"));

	//音量 0-10
	for (int32 i = 0; i < 11; i++)
	{
		VolumeList.Add(FText::AsNumber(i));
	}

	MenuTitle = LOCTEXT("Options", "选项");

	SoundVolumeOption = AddMenuItemWithOptions<FPlatformOptions>(LOCTEXT("SoundVolume", "音量大小"), VolumeList, this, &FPlatformOptions::SoundVolumeOptionChanged);
#if PLATFORM_DESKTOP
	VideoResolutionOption = AddMenuItemWithOptions<FPlatformOptions>(LOCTEXT("Resolution", "分辨率"), ResolutionList, this, &FPlatformOptions::VideoResolutionOptionChanged);
	FullScreenOption = AddMenuItemWithOptions<FPlatformOptions>(LOCTEXT("FullScreen", "分辨率"), OnOffList, this, &FPlatformOptions::FullScreenOptionChanged);
#endif

	//为杂项操作设置一些处理程序。
	SetAcceptHandler<FPlatformOptions>(this,&FPlatformOptions::ApplySettings);
	SetCancelHandler<FPlatformOptions>(this, &FPlatformOptions::DiscardSettings);
	SetOnOpenHandler<FPlatformOptions>(this, &FPlatformOptions::UpdateOptions);

	AddMenuItem(LOCTEXT("AcceptChanges", "应用"),this, &FPlatformOptions::OnAcceptSettings);
	AddMenuItem(LOCTEXT("DiscardChanges", "取消"), this, &FPlatformOptions::OnDiscardSettings);

	UserSettings = CastChecked<UPlatformerGameUser>(GEngine->GetGameUserSettings());
	SoundVolumeOpt = UserSettings->GetSoundVolume();

#if PLATFORM_DESKTOP
	//这保证我们只使用受支持的分辨率。
	//只有在桌面，在其他平台上这样做，这可以调整实际的GSystemResolution，我们不希望-
	//我们想用其他的方法，比如r.MobileContentScaleFactor或r.ScreenPercentage。这种崩溃IOS
	int32 SupportedResolutionIndex = GetCurrentResolutionIndex(UserSettings->GetScreenResolution());
	ResolutionOpt = PlatformerResolutions[SupportedResolutionIndex];
#endif

	bFullScreenOpt = UserSettings->GetFullscreenMode();
}

void FPlatformOptions::ApplySettings()
{
	UserSettings->SetSoundVolume(SoundVolumeOpt);
	UserSettings->SetScreenResolution(ResolutionOpt);
	UserSettings->SetFullscreenMode(bFullScreenOpt);
	UserSettings->ApplySettings(false);
}

void FPlatformOptions::DiscardSettings()
{
	RevertChanges();
}

void FPlatformOptions::UpdateOptions()
{
	//获取用户设置
	UserSettings = CastChecked<UPlatformerGameUser>(GEngine->GetGameUserSettings());
#if PLATFORM_DESKTOP
	VideoResolutionOption->SelectedMultiChoice = GetCurrentResolutionIndex(UserSettings->GetScreenResolution());
	FullScreenOption->SelectedMultiChoice = UserSettings->GetFullscreenMode() != EWindowMode::Windowed ? 1 : 0;
#endif // PLATFORM_DESKTOP

	SoundVolumeOption->SelectedMultiChoice = FMath::TruncToInt(UserSettings->GetSoundVolume() * 10.0f);
}

void FPlatformOptions::RevertChanges()
{
	UpdateOptions();
}

void FPlatformOptions::SoundVolumeOptionChanged(TSharedPtr<FGameMenuItem> MenuItem, int32 MultiOptionIndex)
{
	SoundVolumeOpt = MultiOptionIndex / 10.0f;
}

void FPlatformOptions::VideoResolutionOptionChanged(TSharedPtr<FGameMenuItem> MenuItem, int32 MultiOptionIndex)
{
	ResolutionOpt = PlatformerResolutions[MultiOptionIndex];
}

void FPlatformOptions::FullScreenOptionChanged(TSharedPtr<FGameMenuItem> MenuItem, int32 MultiOptionIndex)
{
	static auto CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.FullScreenMode"));
	auto FullScreenMode = CVar->GetValueOnGameThread() == 1 ? EWindowMode::WindowedFullscreen : EWindowMode::Fullscreen;
	bFullScreenOpt = MultiOptionIndex == 0 ? EWindowMode::Windowed : FullScreenMode;
}
void FPlatformOptions::OnAcceptSettings()
{
	RootMenuPageWidget->MenuGoBack(false);
}
void FPlatformOptions::OnDiscardSettings()
{
	RootMenuPageWidget->MenuGoBack(true);
}
int32 FPlatformOptions::GetCurrentResolutionIndex(FIntPoint CurrentRes)
{
	int32 Result = 0;//如果没有找到匹配，返回第一个有效的分辨率
	for (int32 i = 0; i < PlatformerResCount; i++)
	{
		if (PlatformerResolutions[i] == CurrentRes)
		{
			Result = i;
			break;
		}
	}
	return Result;
}
#undef LOCTEXT_NAMESPACE