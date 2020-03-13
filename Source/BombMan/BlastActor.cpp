// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
ABlastActor::ABlastActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;
	BlastSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlastComponent"));
	BlastSM->SetupAttachment(RootComponent);
	
	InitialLifeSpan = 1.0f;
}

// Called when the game starts or when spawned
void ABlastActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlastActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlastActor::SetupBlast(FVector originPos, FVector endPos)
{
	SetActorLocation(FMath::Lerp(originPos, endPos, 0.5f));
	float strench = FVector::Distance(originPos, endPos) / 100;
	FVector scale = GetActorScale3D();
	scale.X = strench;
	SetActorScale3D(scale);
}

