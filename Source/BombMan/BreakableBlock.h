// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableBlock.generated.h"

class UParticleSystem;
class ABombManGameModeBase;
class APowerActor;

UCLASS()
class BOMBMAN_API ABreakableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnDestroy();

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BreakableBlockSM;

	UPROPERTY(EditAnywhere, Category = "Explosion")
	UParticleSystem* ExplosionPS;

	ABombManGameModeBase* BombManGM;
	UPROPERTY(EditAnywhere, Category = "Explosion")
	TSubclassOf<APowerActor> PowerupAc;
};
