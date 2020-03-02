// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockGeneration.generated.h"

class AUnBreakableBlock;
class ABreakableBlock;

UCLASS()
class BOMBMAN_API ABlockGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockGeneration();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnUnBreakableBlock();
	void SpawnBreakableBlock();

	UFUNCTION(BlueprintCallable)
	void InitValidPosition();

#pragma region DrawDebug
	virtual bool ShouldTickIfViewportsOnly() const override;
	void DrawDebugPos(const FVector& pos, const FLinearColor& color);
#pragma  endregion

private:
	int GetValidPosCount();
	bool AllowSpawnPosition(FVector position);

private:
	UPROPERTY(EditAnywhere, Category = "Block Generation")
	TSubclassOf<AUnBreakableBlock> UnBreakableBlock;
	UPROPERTY(EditAnywhere, Category = "Block Generation")
	TSubclassOf<ABreakableBlock> BreakableBlock;
	UPROPERTY(EditAnywhere, Category = "Block Generation | Settings")
	int Width;
	UPROPERTY(EditAnywhere, Category = "Block Generation | Settings")
	int Height;
	UPROPERTY(EditAnywhere, Category = "Block Generation | Settings")
	float Scale;

	UPROPERTY(EditAnywhere, Category = "Block Generation", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BlockIntensity = 0.7f;

#pragma region DrawDebug
	UPROPERTY(EditAnywhere, Category = "Block Generation")
	bool IsDrawDebug;
	const FLinearColor ValidColor = FLinearColor(0, 0, 0.8f);
	const FLinearColor InValidColor = FLinearColor(0.8f, 0, 0);
#pragma  endregion

	UPROPERTY(EditAnywhere, Category = "Block Generation")
	TArray<FVector> IgnoredPos;	// 主角出生的位置
	UPROPERTY(VisibleAnywhere, Category = "Block Generation")
	TArray<FVector> SpawnPos;	// 备选的合法位置
};
