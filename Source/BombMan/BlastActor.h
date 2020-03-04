// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlastActor.generated.h"

UCLASS()
class BOMBMAN_API ABlastActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlastActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetupBlast(FVector originPos, FVector endPos);

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* BlastSM;

};
