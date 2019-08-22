// Fill out your copyright notice in the Description page of Project Settings.

#include "StreetSectionLevelScriptActor.h"
#include "ActionTestBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ActionTestSaveGame.h"
#include "ActionTest.h"
#include "Curves/CurveFloat.h"
#include "Curves/RichCurve.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AStreetSectionLevelScriptActor::AStreetSectionLevelScriptActor()
{
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Curves/C_MyCurve.C_MyCurve'"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;

	CurveFloat = 0.0f;

}


void AStreetSectionLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	/*FRichCurve* richCurve=new FRichCurve;
	richCurve->AddKey(0.0f, 0.0f);
	richCurve->AddKey(5.0f, 359.0f);

	FloatCurve = NewObject<UCurveFloat>();
	auto list = FloatCurve->GetCurves();
	list.Add(FRichCurveEditInfo(richCurve, FName{ TEXT("SomeCurveName") }));*/

	if (FloatCurve != NULL)
	{
		FOnTimelineFloat onTimelineCallback;
		FOnTimelineEventStatic onTimelineFinishedCallback;

		TimelineComponent = NewObject<UTimelineComponent>(this,TEXT("TimelineComponent"));

		TimelineComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;//来自蓝图以便在重新运行构建脚本时清除它
		this->BlueprintCreatedComponents.Add(TimelineComponent);//添加到数组中，使其保存
		TimelineComponent->SetNetAddressable();//此组件具有可用于复制的稳定名称
		TimelineComponent->SetPropertySetObject(this);//设置时间轴应该在哪个对象上驱动属性
		TimelineComponent->SetDirectionPropertyName(FName("TimelineDirection"));

		TimelineComponent->SetLooping(false);
		TimelineComponent->SetTimelineLength(5.0f);
		TimelineComponent->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		TimelineComponent->SetPlaybackPosition(0.0f, false);

		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		TimelineComponent->AddInterpFloat(FloatCurve, onTimelineCallback, FName{ TEXT("CurveFloat") }, FName{TEXT("NewTrack")});
		TimelineComponent->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		TimelineComponent->RegisterComponent();
	}

	for (int i = 0; i < 10; i++)
	{
		Names.Add(TEXT("PCF"));
		Times.Add(FMath::FRandRange(39, 50));
	}

	UActionTestBlueprintLibrary::SortHighscores( Times, Names, Times, Names, 10);

	Save = UGameplayStatics::LoadGameFromSlot(FString(TEXT("PlatformerSave")),0);

	if (Save == nullptr)
	{
		Save = UGameplayStatics::CreateSaveGameObject(UActionTestSaveGame::StaticClass());

		UpdateSaveHiscores();

		UGameplayStatics::SaveGameToSlot(Save, FString(TEXT("PlatformerSave")),0);
	}
	else 
	{
		UActionTestSaveGame* ActionTestSave = Cast<UActionTestSaveGame>(Save);
		for (int i = 0; i < ActionTestSave->Records.Num(); i++)
		{
			float Time;
			FString Name;
			ActionTestSave->GetRecord(Time, Name, i);
			SetArrayElem<float>(Times, i, Time);
			SetArrayElem<FString>(Names, i, Name);
		}
	}

	if (TimelineComponent != NULL)
	{
		TimelineComponent->PlayFromStart();
	}
}

void AStreetSectionLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimelineComponent != NULL)
	{
		TimelineComponent->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void AStreetSectionLevelScriptActor::UpdateSaveHiscores()
{
	for (int i = 0; i < Times.Num(); i++)
	{
		UActionTestSaveGame* ActionTestSave = Cast<UActionTestSaveGame>(Save);
		ActionTestSave->SetRecord(Times[i],Names[i],i);
	}
}

void AStreetSectionLevelScriptActor::TimelineCallback_Implementation(float val)
{
	UE_LOG(LogActionTest, Log, TEXT("CurveFloat:%f"), CurveFloat);
}

void AStreetSectionLevelScriptActor::TimelineFinishedCallback()
{
	if (TimelineComponent != NULL)
	{
		TimelineComponent->PlayFromStart();
	}
}


