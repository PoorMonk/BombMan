// Fill out your copyright notice in the Description page of Project Settings.


#include "BombActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ABombActor::ABombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BombSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombSM"));
	BombSM->SetupAttachment(RootComponent);
	SparksPar = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SparksPar"));
	SparksPar->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABombActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABombActor::OnOverlapEnd);
}

// Called every frame
void ABombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombActor::OnOverlapEnd(UPrimitiveComponent * OverlapComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetOwner())
	{
		BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}
}

