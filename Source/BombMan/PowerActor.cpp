// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerActor.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BombManCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APowerActor::APowerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UTexture2D> SpeedIcon(TEXT("Texture2D'/Game/_Project/Textures/SpeedIcon.SpeedIcon'"));
	Sprites.Add(SpeedIcon.Object);
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> BombIcon(TEXT("Texture2D'/Game/_Project/Textures/BombIcon.BombIcon'"));
	Sprites.Add(BombIcon.Object);

	static ConstructorHelpers::FObjectFinder<UTexture2D> LongerBlastsIcon(TEXT("Texture2D'/Game/_Project/Textures/LongerBlastsIcon.LongerBlastsIcon'"));
	Sprites.Add(LongerBlastsIcon.Object);

	static ConstructorHelpers::FObjectFinder<UTexture2D> RemoteIcon(TEXT("Texture2D'/Game/_Project/Textures/RemoteIcon.RemoteIcon'"));
	Sprites.Add(RemoteIcon.Object);


	Billboard->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void APowerActor::BeginPlay()
{
	Super::BeginPlay();

	int TempRand = FMath::RandRange(0, 3);

	PowerupType = static_cast<EPowerupType>(TempRand);
	
	Billboard->SetSprite(Sprites[TempRand]);
}

void APowerActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ABombManCharacter* BombManCharacter = Cast<ABombManCharacter>(OtherActor);
	if (BombManCharacter)
	{
		switch (PowerupType)
		{
		case EPowerupType::SpeedBoost:
			BombManCharacter->GetCharacterMovement()->MaxWalkSpeed += SpeedIncrement;
			break;
		case EPowerupType::MoreBombs:
			BombManCharacter->AddBombLimit();
			break;
		case EPowerupType::LongerBlast: 
			BombManCharacter->AddBlastRange();
			break;
		case EPowerupType::RemoteBomb:
			BombManCharacter->SetHasRemote();
			break;
		default:
			break;
		}
		Destroy();
	}
}

// Called every frame
void APowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

