// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MultiplayerGameMode.h"
#include "MultiplayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

#define OUT

// Sets default values
ACamera::ACamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay(){
	Super::BeginPlay();
	ClassSetup();
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACamera::ClassSetup(){
	GameMode = Cast<AMultiplayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	PlayerRefs = GameMode->Players;
	TArray<AActor*> ControllerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), ControllerActors);
	for (AActor* CurrentActor : ControllerActors) {
		APlayerController* CurrentController = Cast<APlayerController>(CurrentActor);
		CurrentController->SetViewTargetWithBlend(this);
	}
	int i = 0;
	for (AActor* CurrentPlayer : PlayerRefs) {
		switch (i)
		{
		case(0):
			P1 = Cast<AMultiplayerCharacter>(CurrentPlayer);
		case(1):
			P2 = Cast<AMultiplayerCharacter>(CurrentPlayer);
		case(2):
			P3 = Cast<AMultiplayerCharacter>(CurrentPlayer);
		case(3):
			P4 = Cast<AMultiplayerCharacter>(CurrentPlayer);
		default:
			break;
		}
	}
}

