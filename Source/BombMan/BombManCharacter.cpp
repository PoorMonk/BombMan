// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManCharacter.h"

// Sets default values
ABombManCharacter::ABombManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

