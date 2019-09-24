// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestGameMode.h"
#include "ActionTestPlayerController.h"
#include "ActionTestHUD.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "PlayerPawn.h"
#include "ActionTestCharacter.h"
#include "TimerManager.h"

AActionTestGameMode::AActionTestGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerControllerClass = AActionTestPlayerController::StaticClass();

	HUDClass = AActionTestHUD::StaticClass();

	DefaultPawnClass = APlayerPawn::StaticClass();

	GameState = EGameState::Intro;

	if ((GEngine != NULL) && (GEngine->GameViewport != NULL))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}


void AActionTestGameMode::PrepareRound(bool bRestarting)
{
	if (bRestarting)
	{
		OnRoundFinished.Broadcast();
	}

	GameState = bRestarting ? EGameState::Restarting : EGameState::Waiting;
	bRoundWasWon = false;
	RoundStartTime = 0.0f;

	AActionTestPlayerController* PC = Cast<AActionTestPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	AActionTestCharacter* Pawn = PC ? Cast<AActionTestCharacter>(PC->GetPawn()) : NULL;
	if (Pawn)
	{
		Pawn->OnRoundReset();

		AActor* StartSpot = FindPlayerStart(PC);
		Pawn->TeleportTo(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());

		if (Pawn->bHidden)
		{
			Pawn->SetActorHiddenInGame(false);
		}
	}
}

EGameState::Type AActionTestGameMode::GetGameState() const
{
	return GameState;
}

void AActionTestGameMode::SetCanBeRestarted(bool bAllowRestart)
{
	if (GameState == EGameState::Finished)
	{
		bCanBeRestarted = bAllowRestart;
	}
}

bool AActionTestGameMode::IsRoundInProgress() const
{
	return GameState == EGameState::Playing;
}

void AActionTestGameMode::StartRound()
{
	RoundStartTime = GetWorld()->GetTimeSeconds();
	GameState = EGameState::Playing;
}

void AActionTestGameMode::ModifyRoundDuration(float DeltaTime, bool bIncrease)
{
	if (IsRoundInProgress())
	{
		const float PrevRoundStartTime = RoundStartTime;
		const float Delta = FMath::Abs(DeltaTime);
		if (bIncrease)
		{
			RoundStartTime -= Delta;
		}
		else
		{
			const float CurrTime = GetWorld()->GetTimeSeconds();
			RoundStartTime += Delta;
			RoundStartTime = FMath::Min(RoundStartTime, CurrTime);
		}

		APlayerController* PC = GEngine->GetFirstLocalPlayerController(GetWorld());
		AActionTestHUD* HUD = PC ? Cast<AActionTestHUD>(PC->MyHUD) : NULL;
		if (HUD)
		{
			HUD->NotifyRoundTimeModified(PrevRoundStartTime - RoundStartTime);
		}
	}
}

float AActionTestGameMode::GetCurrentCheckpointTime(int32 CheckpointID) const
{
	return CurrentTimes.IsValidIndex(CheckpointID) ? CurrentTimes[CheckpointID] : -1.0f;
}

float AActionTestGameMode::GetBestCheckpointTime(int32 CheckpointID) const
{
	return BastTimes.IsValidIndex(CheckpointID) ? BastTimes[CheckpointID] : -1.0f;
}

void AActionTestGameMode::SaveCheckpointTime(int32 CheckpointID)
{
	if (CheckpointID < 0)
	{
		return;
	}

	//保存当前时间
	while (CheckpointID >= CurrentTimes.Num())
	{
		CurrentTimes.Add(-1.0f);
	}

	CurrentTimes[CheckpointID] = GetRoundDuration();
}

void AActionTestGameMode::FinishRound()
{
	GameState = EGameState::Finished;

	//确定游戏状态
	const int32 LastCheckpointIdx = GetNumCheckpoints() - 1;
	const float BestTime = GetBestCheckpointTime(LastCheckpointIdx);
	bRoundWasWon = (BestTime < 0) || (GetRoundDuration() < BestTime);

	//通知玩家
	APlayerController* PC = GEngine->GetFirstLocalPlayerController(GetWorld());
	AActionTestCharacter* Pawn = PC ? Cast<AActionTestCharacter>(PC->GetPawn()) : NULL;
	if (Pawn)
	{
		Pawn->OnRoundFinished();
	}

	//更新最佳检查点时间
	while (LastCheckpointIdx >= BastTimes.Num())
	{
		BastTimes.Add(-1.0f);
	}

	for (int32 i = 0; i < BastTimes.Num(); i++)
	{
		if ((BastTimes[i] < 0) || (BastTimes[i] > CurrentTimes[i]))
		{
			BastTimes[i] = CurrentTimes[i];
		}
	}
}

bool AActionTestGameMode::IsRoundWon() const
{
	return bRoundWasWon;
}

float AActionTestGameMode::GetRoundDuration() const
{
	if (IsRoundInProgress())
	{
		const float CurrTime = GetWorld()->GetTimeSeconds();
		return CurrTime - RoundStartTime;
	}

	const int32 LastCheckpoint = GetNumCheckpoints() - 1;
	return GetBestCheckpointTime(LastCheckpoint);
}

int32 AActionTestGameMode::GetNumCheckpoints() const
{
	return FMath::Max(CurrentTimes.Num(), BastTimes.Num());
}

bool AActionTestGameMode::CanBeRestarted() const
{
	return (GameState == EGameState::Finished && bCanBeRestarted);
}

void AActionTestGameMode::TryRestartRound()
{
	if (CanBeRestarted())
	{
		PrepareRound(true);
		GetWorldTimerManager().SetTimer(TimerHandle_StartRound,this,&AActionTestGameMode::StartRound,2.0f,false);
		bCanBeRestarted = false;
	}
}
