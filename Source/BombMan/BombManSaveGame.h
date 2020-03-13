// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BombManSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BOMBMAN_API UBombManSaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()	// ��Ҫ��Ӻ����ݲŻᱣ��
	int P1_Victories;
	UPROPERTY()	// ��Ҫ��Ӻ����ݲŻᱣ��
	int P2_Victories;

	UBombManSaveGame();

public:
	FORCEINLINE int GetP1Victories() { return P1_Victories; }
	FORCEINLINE int GetP2Victories() { return P2_Victories; }

	void IncreaseP1Victories() { P1_Victories++; }
	void IncreaseP2Victories() { P2_Victories++; }


};
