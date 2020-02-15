// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerGameMode.generated.h"

class APlayerStart;

UCLASS(minimalapi)
class AMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	AMultiplayerGameMode();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	TArray<AActor*> GetPlayerStartPoints();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SpawnPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int MaxPlayerCout = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	TArray<AActor*> Players;
};



