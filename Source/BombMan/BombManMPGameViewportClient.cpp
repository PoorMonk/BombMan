// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManMPGameViewportClient.h"

//bool UBombManMPGameViewportClient::InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad)
bool UBombManMPGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (IgnoreInput() || EventArgs.IsGamepad() || EventArgs.Key.IsMouseButton())
	{
		return Super::InputKey(EventArgs);
	}
	else
	{
		UEngine* const Engine = GetOuterUEngine();
		const int32 NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
		bool bRet = true;
		FInputKeyEventArgs inputParams = FInputKeyEventArgs(EventArgs);
		for (int32 i = 0; i < NumPlayers; ++i)
		{
			inputParams.ControllerId = i;
			bRet = Super::InputKey(inputParams) && bRet;
		}
		return bRet;
	}
}

bool UBombManMPGameViewportClient::InputAxis(FViewport * InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if (IgnoreInput() || bGamepad || Key.IsMouseButton())
	{
		return Super::InputAxis(InViewport, ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
	}
	else
	{
		UEngine* const Engine = GetOuterUEngine();
		const int32 NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
		bool bRet = true;
		for (int32 i = 0; i < NumPlayers; ++i)
		{
			bRet = Super::InputAxis(InViewport, i, Key, Delta, DeltaTime, NumSamples, bGamepad) && bRet;
		}
		return bRet;
	}
}
