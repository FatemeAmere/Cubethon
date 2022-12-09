// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CubeScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUBETHON_API UCubeScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetText(float distance);
	
};
