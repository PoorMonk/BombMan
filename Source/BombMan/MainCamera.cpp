// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTargetWithBlend(this, 0);
}
