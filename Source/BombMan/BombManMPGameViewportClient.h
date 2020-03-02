// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "BombManMPGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class BOMBMAN_API UBombManMPGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
protected:
	//virtual bool InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed /* = 1.f */, bool bGamepad /* = false */) override;
	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	virtual bool InputAxis(FViewport* InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples/* =1 */, bool bGamepad/* =false */) override;
};
