// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "BombManGameModeBase.h"
#include "PowerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABreakableBlock::ABreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BreakableBlockSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BreakableBlockSM"));
	RootComponent = BreakableBlockSM;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> explosionPS(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	ExplosionPS = explosionPS.Object;

	static ConstructorHelpers::FClassFinder<APowerActor> powerup(TEXT("/Game/Blueprints/BP_PowerActor"));
	PowerupAc = powerup.Class;
	
}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	
	BombManGM = Cast<ABombManGameModeBase>(GetWorld()->GetAuthGameMode());
	//BombManGM = Cast<ABombManGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

}

void ABreakableBlock::OnDestroy()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionPS, GetActorLocation(), GetActorRotation());

	float TempFloat = FMath::RandRange(0.0f, 1.0f);
	if (TempFloat < BombManGM->GetDropProbability())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(TempFloat));
		GetWorld()->SpawnActor<APowerActor>(PowerupAc, GetActorLocation(), GetActorRotation());
	}

	Destroy();
}

