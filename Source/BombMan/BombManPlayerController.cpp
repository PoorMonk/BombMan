// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/LocalPlayer.h"
#include "BombManCharacter.h"

void ABombManPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABombManPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	int32 id = GetLocalPlayer()->GetControllerId();
	if (id == 0)
	{
		InputComponent->BindAxis("MoveForward_P1", this, &ABombManPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight_P1", this, &ABombManPlayerController::MoveRight);
		InputComponent->BindAction("Bomb_P1", IE_Pressed, this, &ABombManPlayerController::SpawnBombInput);
		InputComponent->BindAction("RemoteDenotate_P1", IE_Pressed, this, &ABombManPlayerController::RemoteDenotateInput);
	}
	else if (id == 1)
	{
		InputComponent->BindAxis("MoveForward_P2", this, &ABombManPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight_P2", this, &ABombManPlayerController::MoveRight);
		InputComponent->BindAction("Bomb_P2", IE_Pressed, this, &ABombManPlayerController::SpawnBombInput);
		InputComponent->BindAction("RemoteDenotate_P2", IE_Pressed, this, &ABombManPlayerController::RemoteDenotateInput);
	}
}

void ABombManPlayerController::MoveForward(float AxisValue)
{
	Pawn = GetPawn();
	if (Pawn)
	{
		Pawn->AddMovementInput(FVector::ForwardVector, AxisValue);
	}
}

void ABombManPlayerController::MoveRight(float AxisValue)
{
	Pawn = GetPawn();
	if (Pawn)
	{
		Pawn->AddMovementInput(FVector::RightVector, AxisValue);
	}
}

void ABombManPlayerController::SpawnBombInput()
{
	Pawn = GetPawn();
	if (Pawn)
	{
		ABombManCharacter* PlayerController = Cast<ABombManCharacter>(Pawn);
		if (PlayerController)
		{
			PlayerController->SpawnBomb();
		}
	}
}

void ABombManPlayerController::RemoteDenotateInput()
{
	Pawn = GetPawn();
	if (Pawn)
	{
		ABombManCharacter* PlayerController = Cast<ABombManCharacter>(Pawn);
		if (PlayerController)
		{
			if (PlayerController->IsHasRemote())
			{
				PlayerController->Detonate();
			}
		}
	}
}
