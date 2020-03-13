// Fill out your copyright notice in the Description page of Project Settings.


#include "BombActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "BlastActor.h"
#include "Engine/World.h"
#include "BreakableBlock.h"
#include "BombManCharacter.h"
#include "BombManGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

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

	bombManCharacter = Cast<ABombManCharacter>(GetOwner());

	if (bombManCharacter->IsHasRemote())
	{
	}
	else
	{
		GetWorldTimerManager().SetTimer(TimeHandle_Detonate, this, &ABombActor::Detonate, TimeDelay_Detonate, false);
	}

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

void ABombActor::Detonate()
{
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	SpawnBlast(FVector::ForwardVector);
	SpawnBlast(FVector::RightVector);

	bombManCharacter->RemoveBomb(this);

	Destroy();
}

FVector ABombActor::LineTraceDirection(FVector direction)
{
	FVector OriginPos = GetActorLocation();
	FVector EndPos = OriginPos + direction * 100 * BlastLength;
	TArray<FHitResult> Hits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	GetWorld()->LineTraceMultiByChannel(Hits, OriginPos, EndPos, ECC_GameTraceChannel1, Params);

	if (Hits.Num() > 0)
	{
		EndPos = Hits.Last().ImpactPoint;
		for (auto hit : Hits)
		{
			ABreakableBlock* BreakableBlock = Cast<ABreakableBlock>(hit.GetActor());
			if (BreakableBlock)
			{
				BreakableBlock->OnDestroy();
			}
			else
			{
				ABombManCharacter* BombManCharacter = Cast<ABombManCharacter>(hit.GetActor());
				if (BombManCharacter)
				{
					FString tempString = "Hit Player";
					UE_LOG(LogTemp, Warning, TEXT("%s"), *tempString);
					//Cast<ABombManGameModeBase>(GetWorld()->GetAuthGameMode())->OnPlayerDeath(BombManCharacter);
					BombManCharacter->OnDeath();
				}
			}
		}
	}

	return EndPos;
}

void ABombActor::SpawnBlast(FVector Direction)
{
	ABlastActor* blashAc = nullptr;
	if (Direction == FVector::RightVector)
	{
		FRotator newRotator;
		newRotator.Pitch = 0.0f;
		newRotator.Yaw = 90.0f;
		newRotator.Roll = 0.0f;
		blashAc = GetWorld()->SpawnActor<ABlastActor>(BlastAc, GetActorLocation(), newRotator);
		//blashAc->SetupBlast(GetActorLocation(), LineTraceDirection(Direction));
	}
	else if (Direction == FVector::ForwardVector)
	{
		blashAc = GetWorld()->SpawnActor<ABlastActor>(BlastAc, GetActorLocation(), FRotator::ZeroRotator);
	}
	blashAc->SetupBlast(LineTraceDirection(-Direction), LineTraceDirection(Direction));
}

void ABombActor::SetBlastRange(float BlastRange)
{
	BlastLength = BlastRange;
}

