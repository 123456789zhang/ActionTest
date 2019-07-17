#include "ActionTestLoadingScreen.h"

#include "MoviePlayer/Public/MoviePlayer.h"
#include "SlateBasics.h"
#include "SlateExtras.h"


struct FActionTestLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FActionTestLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		:FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(nullptr, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		FSlateBrush::AddReferencedObjects(Collector);
	}
};

class SActioTestLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SActioTestLoadingScreen) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs)
	{
		static const FName LoadingScreenName(TEXT("/Game/UI/Menu/LoadingScreen.LoadingScreen"));

		//因为我们这里没有使用游戏风格，所以只加载一个图像
		LoadingScreenBrush = MakeShareable(new FActionTestLoadingScreenBrush(LoadingScreenName, FVector2D(1920, 1080)));

		ChildSlot
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(LoadingScreenBrush.Get())
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Right)
					.Padding(FMargin(10.0f))
					[
						SNew(SThrobber)
						.Visibility(this,&SActioTestLoadingScreen::GetLoadIndicatorVisibility)
					]
				]
			];
		
	}

private:

	EVisibility GetLoadIndicatorVisibility() const
	{
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}

	/** 加载屏幕的画刷 */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FActionTestLoadingScreenModule : public IActionTestLoadingScreenModule
{
public:

	virtual void StartupModule() override
	{
		if (IsMoviePlayerEnabled())
		{
			CreateLoadingScreen();
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen() override
	{
		CreateLoadingScreen();
	}

	void CreateLoadingScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.WidgetLoadingScreen = SNew(SActioTestLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FActionTestLoadingScreenModule, ActionTestLoadingScreen);