// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BombManCharacter.generated.h"

class ABombActor;

UCLASS()
class BOMBMAN_API ABombManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABombManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void SpawnBomb();
	FVector RevisePosition(FVector vector);

	void AddBlastRange();
	void AddBombLimit();
	void SetHasRemote();

	void RemoveBomb(ABombActor* bomeActor);

	FORCEINLINE bool IsHasRemote() { return HasRemote; }
	void Detonate();

	void OnDeath();

private:
	float RevisePosition(int value, float scale);

private:
	UPROPERTY(EditAnywhere, Category = "Bomb")
	TSubclassOf<ABombActor> Bomb;
	UPROPERTY(EditAnywhere, Category = "Bomb")
	float BlastRange = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Bomb")
	float BombLimit = 1.0f;

	TArray<ABombActor*> BombsArr;

	bool HasRemote = false;

	bool IsDead = false;

	class ABombManGameModeBase* GameMode;
};
