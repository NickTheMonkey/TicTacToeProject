// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DATA/Enums/ENUMS.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_General.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_RULES_API UBPFL_General : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Controller")
	static AActor* GetControllerWithSymbol(const PlayersSymbol& l_Symbol);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	static AActor* FindTurningController();
};
