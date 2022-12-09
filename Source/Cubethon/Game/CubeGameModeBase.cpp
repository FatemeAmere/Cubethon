// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGameModeBase.h"

void ACubeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if(ScoreWidgetClass)
	{
		ScoreWidget = Cast<UCubeScoreWidget>( CreateWidget(GetWorld(), ScoreWidgetClass));

		if(ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
}

void ACubeGameModeBase::UpdateText(float distance)
{
	ScoreWidget->SetText(distance);
}

void ACubeGameModeBase::ShowResetMenu()
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("RESTART"));
	if(RestartWidgetClass)
	{
		RestartWidget = Cast<UCubeRestartWidget>( CreateWidget(GetWorld(), RestartWidgetClass));
		
		if(RestartWidget)
		{
			RestartWidget->AddToViewport();
		}
	}
}
