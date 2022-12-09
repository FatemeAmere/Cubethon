// Fill out your copyright notice in the Description page of Project Settings.


#include "CubePlayer.h"

#include "CubeGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACubePlayer::ACubePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACubePlayer::OnOverlap);
	//Mesh->OnComponentHit.AddDynamic(this, &ACubePlayer::OnHit);
}

// Called when the game starts or when spawned
void ACubePlayer::BeginPlay()
{
	Super::BeginPlay();
	NewPosition = GetActorLocation();
	TargetY = GetActorLocation().Y;
	
}
// Called every frame
void ACubePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NewPosition.Y = FMath::Lerp(GetActorLocation().Y, TargetY, HorizontalSpeed*DeltaTime);
	NewPosition.X = GetActorLocation().X + ForwardOffset*DeltaTime;
	SetActorLocation(NewPosition);

	if(CountScore){
	//update text with player Y
		Cast<ACubeGameModeBase>(GetWorld()->GetAuthGameMode())->UpdateText(  static_cast<int>(GetActorLocation().X/1000));
	}
}


// Called to bind functionality to input
void ACubePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Right",IE_Pressed, this, &ACubePlayer::MoveRight);
	InputComponent->BindAction("Left",IE_Pressed, this, &ACubePlayer::MoveLeft);
}

void ACubePlayer::MoveRight()
{
	switch (PlayerPosition)
	{
	case MIDDLE:
		UpdatePosition(RIGHT);
		break;
	case LEFT:
		UpdatePosition(MIDDLE);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("[MoveRight]: Undefined Position State"));
		break;
	}
}

void ACubePlayer::MoveLeft()
{
	switch (PlayerPosition)
	{
	case MIDDLE:
		UpdatePosition(LEFT);
		break;
	case RIGHT:
		UpdatePosition(MIDDLE);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("[MoveLeft]: Undefined Position State"));
		break;
	}
}

void ACubePlayer::UpdatePosition(enum PositionState NewPos)
{
	PlayerPosition = NewPos;
	switch (PlayerPosition)
	{
	case MIDDLE:
		TargetY = 0.0f;
		break;
	case RIGHT:
		TargetY = RightPosition->GetComponentLocation().Y;
		break;
	case LEFT:
		TargetY = -RightPosition->GetComponentLocation().Y;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("[MoveLeft]: Undefined Position State"));
		break;
	}
}

// void ACubePlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
// 	FVector NormalImpulse, const FHitResult& Hit)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, TEXT("OnHit"));
// }

void ACubePlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, TEXT("OnOverlap"));
	if(OtherActor->ActorHasTag("Obstacle"))
	{
		Mesh->SetVisibility(false);
		SetActorTickEnabled(false);
		Cast<ACubeGameModeBase>(GetWorld()->GetAuthGameMode())->ShowResetMenu();
	}
	else if(OtherActor->ActorHasTag("End"))
	{
		CountScore = false;
		SpringArm->K2_DetachFromComponent(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, true);
		Cast<ACubeGameModeBase>(GetWorld()->GetAuthGameMode())->EndGame();
	}
}

