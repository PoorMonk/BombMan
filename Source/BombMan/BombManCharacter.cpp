// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BombActor.h"
#include "Engine/World.h"

// Sets default values
ABombManCharacter::ABombManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ABombActor> tempBomb(TEXT("/Game/Blueprints/BP_BombActor"));
	Bomb = tempBomb.Class;
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
	if (Bomb)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		GetWorld()->SpawnActor<ABombActor>(Bomb, GetActorLocation(), FRotator::ZeroRotator, Params);
	}
}

float ABombManCharacter::RevisePosition(int value, float scale)
{
	float remains = value % (int)scale;
	return FMath::Abs(remains) > scale / 2 ? value - remains + (value > 0 ? scale : -scale) : value - remains;
}

