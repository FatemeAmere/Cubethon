// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeRestartWidget.h"
#include "CubeScoreWidget.h"
#include "GameFramework/GameModeBase.h"
#include "CubeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CUBETHON_API ACubeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> ScoreWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> RestartWidgetClass;

	UPROPERTY()
	UCubeScoreWidget* ScoreWidget;
	UPROPERTY()
	UCubeRestartWidget* RestartWidget;

	virtual void BeginPlay() override;

public:
	void UpdateText(float distance);
	void ShowResetMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void EndGame();
};


