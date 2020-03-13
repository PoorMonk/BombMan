// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BomberHUD.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class BOMBMAN_API UBomberHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RemainTime;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* P1_Text;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* P2_Text;
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* WinTitle;
	UPROPERTY(Meta = (BindWidget))
	class UButton* RestartBtn;
	UPROPERTY(Meta = (BindWidget))
	class UCanvasPanel* MenuBackground;

public:
	void SetRemainTime(FText timeText);
	void SetP1Text(int score);
	void SetP2Text(int score);
	void SetWintitleText(FText titleText);
	void SetMenuBackground();
	UFUNCTION()
	void OnRestartBtnClicked();

	virtual bool Initialize() override;
};
