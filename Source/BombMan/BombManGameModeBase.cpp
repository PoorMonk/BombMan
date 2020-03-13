// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "BombManGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "BombManPlayerController.h"
#include "BombManCharacter.h"
#include "Kismet/KismetStringLibrary.h"
#include "BomberHUD.h"
#include "Kismet/GameplayStatics.h"
#include "BombManSaveGame.h"
#include "BombManCharacter.h"

ABombManGameModeBase::ABombManGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;	// 为真时Tick才会调用

	static ConstructorHelpers::FClassFinder<ABombManCharacter> BombManC(TEXT("/Game/Blueprints/BP_BombManCharacter"));
	DefaultPawnClass = BombManC.Class;

	PlayerControllerClass = ABombManPlayerController::StaticClass();
}

void ABombManGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TotalTime -= DeltaSeconds;
	TextTime = FText::FromString(UKismetStringLibrary::TimeSecondsToString(TotalTime));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *tempString);
	BomberHUD->SetRemainTime(TextTime);
}

void ABombManGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	BomberHUD = CreateWidget<UBomberHUD>(GetWorld(), LoadClass<UBomberHUD>(this, TEXT("WidgetBlueprint'/Game/Blueprints/WBP_HUD.WBP_HUD_C'")));//要加_C
	BomberHUD->AddToViewport();

	BombManSG = Cast<UBombManSaveGame>(UGameplayStatics::CreateSaveGameObject(UBombManSaveGame::StaticClass()));
}

void ABombManGameModeBase::OnPlayerDeath(AController* Controller)
{
	ABombManPlayerController* BombManPlayerController = Cast<ABombManPlayerController>(Controller);
	if (UGameplayStatics::GetPlayerControllerID(BombManPlayerController) == 0)
	{
		BomberHUD->SetWintitleText(FText::FromString("Player 2 Wins"));
		IncreamentP2Victories();
	}
	else if (UGameplayStatics::GetPlayerControllerID(BombManPlayerController) == 1)
	{
		BomberHUD->SetWintitleText(FText::FromString("Player 1 Wins"));
		IncreamentP1Victories();
	}
	UpdateScore();
	BomberHUD->SetMenuBackground();
	OnGameEnd();
}

void ABombManGameModeBase::IncreamentP1Victories()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		BombManSG = Cast<UBombManSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	else
	{
		BombManSG = Cast<UBombManSaveGame>(UGameplayStatics::CreateSaveGameObject(UBombManSaveGame::StaticClass()));
	}
	BombManSG->IncreaseP1Victories();
	UGameplayStatics::SaveGameToSlot(BombManSG, SaveSlotName, UserIndex);
}

void ABombManGameModeBase::IncreamentP2Victories()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		BombManSG = Cast<UBombManSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	else
	{
		BombManSG = Cast<UBombManSaveGame>(UGameplayStatics::CreateSaveGameObject(UBombManSaveGame::StaticClass()));
	}
	BombManSG->IncreaseP2Victories();
	UGameplayStatics::SaveGameToSlot(BombManSG, SaveSlotName, UserIndex);
}

void ABombManGameModeBase::UpdateScore()
{
	BomberHUD->SetP1Text(BombManSG->GetP1Victories());
	BomberHUD->SetP2Text(BombManSG->GetP2Victories());
}

void ABombManGameModeBase::OnGameEnd()
{
	UGameplayStatics::SetGamePaused(this, true);
	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;
}

void ABombManGameModeBase::ReStart()
{
	UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(this, 1), Destroy());
	UGameplayStatics::OpenLevel(this, "Level01");
}
