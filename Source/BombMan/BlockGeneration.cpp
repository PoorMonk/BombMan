// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockGeneration.h"
#include "UnBreakableBlock.h"
#include "BreakableBlock.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABlockGeneration::ABlockGeneration() : Width(15), Height(15), Scale(100.0f), IsDrawDebug(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = WITH_EDITOR;

	static ConstructorHelpers::FClassFinder<AUnBreakableBlock> UBBlock(TEXT("/Game/Blueprints/BP_UnBreakableBlock"));
	UnBreakableBlock = UBBlock.Class;
	static ConstructorHelpers::FClassFinder<ABreakableBlock> BBlock(TEXT("/Game/Blueprints/BP_BreakableBlock"));
	BreakableBlock = BBlock.Class;

	IgnoredPos.Add(FVector(-700, 700, 0));
	IgnoredPos.Add(FVector(-700, 600, 0));
	IgnoredPos.Add(FVector(-600, 700, 0));

	IgnoredPos.Add(FVector(700, -700, 0));
	IgnoredPos.Add(FVector(700, -600, 0));
	IgnoredPos.Add(FVector(600, -700, 0));
}

// Called when the game starts or when spawned
void ABlockGeneration::BeginPlay()
{
	Super::BeginPlay();
	
	IsDrawDebug = false;
	SpawnUnBreakableBlock();
	SpawnBreakableBlock();
}

// Called every frame
void ABlockGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDrawDebug)
	{
		for (auto&point : SpawnPos)
		{
			DrawDebugPos(point, ValidColor);
		}
		for (auto&point : IgnoredPos)
		{
			DrawDebugPos(point, InValidColor);
		}
	}
}

void ABlockGeneration::SpawnUnBreakableBlock()
{
	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			if ((i % 2) && (j % 2))
			{
				FVector position = FVector(i - 7, j - 7, 0) * Scale;
				GetWorld()->SpawnActor<AUnBreakableBlock>(UnBreakableBlock, position, FRotator::ZeroRotator);
			}
			
		}
	}
}

void ABlockGeneration::SpawnBreakableBlock()
{
	if (BreakableBlock)
	{
		int BreakableBlockNums = GetValidPosCount() * BlockIntensity;
		TArray<FVector> tempPos;
		tempPos.Append(SpawnPos);
		int index;
		for (int i = 0; i < BreakableBlockNums; ++i)
		{
			index = FMath::RandRange(0, tempPos.Num() - 1);
			GetWorld()->SpawnActor<ABreakableBlock>(BreakableBlock, tempPos[index], FRotator::ZeroRotator);
			tempPos.RemoveAt(index);
		}
	}
}

int ABlockGeneration::GetValidPosCount()
{
	return SpawnPos.Num();
}

bool ABlockGeneration::AllowSpawnPosition(FVector position)
{
	if (IgnoredPos.Contains(position))
	{
		return false;
	}
	return true;
}

void ABlockGeneration::InitValidPosition()
{
	if (SpawnPos.Num() > 0)
	{
		SpawnPos.Empty();
	}

	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			if (!(i % 2) || !(j % 2))
			{
				FVector position = FVector(i - 7, j - 7, 0) * Scale;
				if (AllowSpawnPosition(position))
				{
					SpawnPos.Add(position);
				}
			}
		}
	}
}

bool ABlockGeneration::ShouldTickIfViewportsOnly() const
{
	return WITH_EDITOR;
}

void ABlockGeneration::DrawDebugPos(const FVector & pos, const FLinearColor & color)
{
	UKismetSystemLibrary::DrawDebugPoint(this, pos, 20.0f, color);
}
