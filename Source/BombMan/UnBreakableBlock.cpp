// Fill out your copyright notice in the Description page of Project Settings.


#include "UnBreakableBlock.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AUnBreakableBlock::AUnBreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UnBreakableBlockSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnBreakableBlockSM"));
	RootComponent = UnBreakableBlockSM;
}

// Called when the game starts or when spawned
void AUnBreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnBreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

