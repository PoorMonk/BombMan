// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MainCamera.generated.h"

/**
 * 
 */
UCLASS()
class BOMBMAN_API AMainCamera : public ACameraActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	APlayerController* PlayerController;
};
