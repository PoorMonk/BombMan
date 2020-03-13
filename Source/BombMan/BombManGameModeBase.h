// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombManGameModeBase.generated.h"

UENUM()
enum class EPowerupType : uint8
{
	SpeedBoost,	//加速度
	MoreBombs,	//加炸弹
	LongerBlast,//加范围
	RemoteBomb,	//遥控炸弹
};

/**
 * 
 */
UCLASS()
class BOMBMAN_API ABombManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABombManGameModeBase();

protected:
	UPROPERTY(EditAnywhere, Category = "Powerup")
	float DropProbability = 0.4;
	UPROPERTY(EditAnywhere, Category = "Time")
	float TotalTime = 300.0f;	//倒计时

	FText TextTime;
	class UBomberHUD* BomberHUD;
	class UBombManSaveGame* BombManSG;

	FString SaveSlotName = "MatchValue";
	int UserIndex = 0;

public:
	FORCEINLINE float GetDropProbability() { return DropProbability; }
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	void OnPlayerDeath(AController* Controller);

	void IncreamentP1Victories();
	void IncreamentP2Victories();

	void UpdateScore();

	void OnGameEnd();

	void ReStart();
};
