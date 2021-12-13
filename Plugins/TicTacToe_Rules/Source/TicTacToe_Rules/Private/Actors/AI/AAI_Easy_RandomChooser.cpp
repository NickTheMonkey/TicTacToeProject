// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/AAI_Easy_RandomChooser.h"

int32 AAAI_Easy_RandomChooser::CalculateTurn(const int32& l_Width, const int32& l_Height, const TArray<PlayersSymbol>& board)
{
	if(board.Num() > 0)
	{
		TArray<int32> filtered;

		// поиск свободных тайлов
		for(int32 a = 0; a < board.Num(); a++)
		{
			if(board[a] == PlayersSymbol::PSymb_None)
			{
				filtered.Add(a);
			}
		}

		int32 result = FMath::RandRange(0, filtered.Num() - 1); // выбор случайного элемента из массива выбранных пустых тайлов
		if(filtered.IsValidIndex(result))
		{
			result = filtered[result];
			return result;
		}
	}

	return -1;
}
