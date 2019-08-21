// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTestGameMode.h"
#include "ActionTestPlayerController.h"
#include "ActionTestHUD.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "PlayerPawn.h"

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
}
