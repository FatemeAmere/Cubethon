// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CubePlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;

enum PositionState {LEFT, MIDDLE, RIGHT };

UCLASS()
class CUBETHON_API ACubePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACubePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UChildActorComponent* RightPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	float ForwardOffset = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	float HorizontalSpeed = 0.1f;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void MoveRight();
	void MoveLeft();
	void UpdatePosition(enum PositionState);

	enum PositionState PlayerPosition = MIDDLE;
	float TargetY;
	FVector NewPosition;
	bool CountScore = true;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// UFUNCTION()
	// void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
