// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ENUMS.Generated.h"

UENUM(BlueprintType)
enum class PlayersSymbol: uint8
{
	PSymb_None		UMETA(DisplayName = "None"),
	PSymb_Cross		UMETA(DisplayName = "Cross"),
	PSymb_Circle	UMETA(DisplayName = "Circle"),

	PSymb_Count		UMETA(DisplayName = "Symbols types amount")
};