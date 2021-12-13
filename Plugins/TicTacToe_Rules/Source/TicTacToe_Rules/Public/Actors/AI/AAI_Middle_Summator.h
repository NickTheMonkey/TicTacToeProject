// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/AI/AAI_Base.h"
#include "AAI_Middle_Summator.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_RULES_API AAAI_Middle_Summator : public AAAI_Base
{
	GENERATED_BODY()
	
	protected:
	virtual int32 CalculateTurn(const int32& l_Width, const int32& l_Height, const TArray<PlayersSymbol>& board) override;

	// функция для подсчета очков. Хранятся в буффере, пока рассматриваемый тайл не будет пуст. Пустому тайлу даются очки из буффера. Буффер обнуляется. Тайл добавляется в массив freeFields
	void Counter(TMap<int32, float>& freeFields, float& priceCurrent, const float& priceEqual, const float& priceEnemy, const int32& X, const int32& Y, const int32& width, const TArray<PlayersSymbol>& board);

};
