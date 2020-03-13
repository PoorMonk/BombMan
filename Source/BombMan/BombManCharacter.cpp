// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BombActor.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BombManGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABombManCharacter::ABombManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ABombActor> tempBomb(TEXT("/Game/Blueprints/BP_BombActor"));
	Bomb = tempBomb.Class;

	GetCharacterMovement()->MaxWalkSpeed = 450.0f;

	//GameMode = Cast<ABombManGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode = Cast<ABombManGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called when the game starts or when spawned
void ABombManCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABombManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABombManCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABombManCharacter::MoveRight);
}

void ABombManCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(FVector::ForwardVector, AxisValue);
}

void ABombManCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(FVector::RightVector, AxisValue);
}

void ABombManCharacter::SpawnBomb()
{
	if (BombsArr.Num() >= BombLimit)
	{
		return;
	}
	if (Bomb)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		ABombActor* BombAc = GetWorld()->SpawnActor<ABombActor>(Bomb, RevisePosition(GetActorLocation()), FRotator::ZeroRotator, Params);
		BombAc->SetBlastRange(BlastRange);
		BombsArr.Add(BombAc);
	}
}

FVector ABombManCharacter::RevisePosition(FVector vector)
{
	return FVector(RevisePosition(vector.X, 100), RevisePosition(vector.Y, 100), 0);
}

void ABombManCharacter::AddBlastRange()
{
	BlastRange++;
}

void ABombManCharacter::AddBombLimit()
{
	BombLimit++;
}

void ABombManCharacter::SetHasRemote()
{
	HasRemote = true;
}

void ABombManCharacter::RemoveBomb(ABombActor* bomeActor)
{
	if (BombsArr.Contains(bomeActor))
	{
		BombsArr.Remove(bomeActor);
	}
}

void ABombManCharacter::Detonate()
{
	for (int i = 0; i < BombsArr.Num();)
	{
		BombsArr[i]->Detonate();		
	}
}

void ABombManCharacter::OnDeath()
{
	
	static int count = 0;
	if (!IsDead)
	{
		IsDead = true;
		GameMode->OnPlayerDeath(GetController());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(++count));
	}
}

float ABombManCharacter::RevisePosition(int value, float scale)
{
	float remains = value % (int)scale;
	return FMath::Abs(remains) > scale / 2 ? value - remains + (value > 0 ? scale : -scale) : value - remains;
}

