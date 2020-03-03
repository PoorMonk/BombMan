// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class BOMBMAN_API ABombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* BombSM;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent* SparksPar;
};
