// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/AI/AAI_Base.h"
#include "AAI_Easy_RandomChooser.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_RULES_API AAAI_Easy_RandomChooser : public AAAI_Base
{
	GENERATED_BODY()

protected:
	// функция, в которой будет находиться алгоритм рассчета хода
	//UFUNCTION()
	virtual int32 CalculateTurn(int32& l_Width, int32& l_Height, const TArray<PlayersSymbol>& board) override;
};
