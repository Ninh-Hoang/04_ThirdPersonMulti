// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera.generated.h"

class AMultiplayerGameMode;
class AMultiplayerCharacter;

UCLASS()
class MULTIPLAYER_API ACamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ClassSetup();

	AMultiplayerGameMode* GameMode;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> PlayerRefs;

	AMultiplayerCharacter* P1;
	AMultiplayerCharacter* P2;
	AMultiplayerCharacter* P3;
	AMultiplayerCharacter* P4;
};
