// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombManGameModeBase.h"
#include "PowerActor.generated.h"

class UBoxComponent;
class UBillboardComponent;

UCLASS()
class BOMBMAN_API APowerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBillboardComponent* Billboard;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TArray<UTexture2D*> Sprites;

	EPowerupType PowerupType;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	float SpeedIncrement = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Powerup")
	float BlastRangeIncrement = 1.0f;
};
