// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MultiplayerGameMode.h"
#include "MultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "GameplayTags.h"
#include "MultiplayerCharacter.h"


#define OUT

AMultiplayerGameMode::AMultiplayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMultiplayerGameMode::BeginPlay() {
	Super::BeginPlay();
	SpawnPlayer();
}

TArray<AActor*> AMultiplayerGameMode::GetPlayerStartPoints(){
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OUT PlayerStarts);
	return PlayerStarts;
}

void AMultiplayerGameMode::SpawnPlayer() {
	for (int i = 0; i < MaxPlayerCout; i++) {
		for (AActor* ActorIndex : GetPlayerStartPoints()) {
			APlayerStart* CurrentPlayer = Cast<APlayerStart>(ActorIndex);
			FString StringI = FString::FromInt(i);
			FName CurrentTagInt = FName(*FString::FromInt(i));
			if (CurrentPlayer->PlayerStartTag.IsEqual(CurrentTagInt)) {
				UE_LOG(LogTemp, Warning, TEXT("Player %s SpawnPoint found"), *CurrentPlayer->GetName());
				UGameplayStatics::CreatePlayer(GetWorld(), i);

				UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_Player")));
				UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);

				if (!SpawnActor){
					UE_LOG(LogTemp, Warning, TEXT("CANT FIND OBJECT TO SPAWN"));
					return;
				}

				UClass* SpawnClass = SpawnActor->StaticClass();
				if (SpawnClass == NULL){
					UE_LOG(LogTemp, Warning, TEXT("CLASS == NULL"));
					return;
				}

				UWorld* World = GetWorld();
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AMultiplayerCharacter* PlayerPawn = World->SpawnActor<AMultiplayerCharacter>(GeneratedBP->GeneratedClass, CurrentPlayer->GetActorLocation(), CurrentPlayer->GetActorRotation(), SpawnParams);

				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), i);
				PlayerController->Possess(PlayerPawn);
				Players.AddUnique(PlayerPawn);
			}
		}
	}
}