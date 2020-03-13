// Fill out your copyright notice in the Description page of Project Settings.


#include "BomberHUD.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "BombManGameModeBase.h"

void UBomberHUD::SetRemainTime(FText timeText)
{
	RemainTime->SetText(timeText);
}

void UBomberHUD::SetP1Text(int score)
{
	P1_Text->SetText(FText::AsNumber(score));
}

void UBomberHUD::SetP2Text(int score)
{
	P2_Text->SetText(FText::AsNumber(score));
}

void UBomberHUD::SetWintitleText(FText titleText)
{
	WinTitle->SetText(titleText);
}

void UBomberHUD::SetMenuBackground()
{
	MenuBackground->SetVisibility(ESlateVisibility::Visible);
}

void UBomberHUD::OnRestartBtnClicked()
{
	Cast<ABombManGameModeBase>(UGameplayStatics::GetGameMode(this))->ReStart();
}

// 在初始化函数中注册按钮事件
bool UBomberHUD::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	RestartBtn->OnClicked.AddDynamic(this, &UBomberHUD::OnRestartBtnClicked);
	return true;
}
