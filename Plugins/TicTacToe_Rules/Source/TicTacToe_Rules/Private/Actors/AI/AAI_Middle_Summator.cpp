// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/AAI_Middle_Summator.h"

int32 AAAI_Middle_Summator::CalculateTurn(const int32& l_Width, const int32& l_Height, const TArray<PlayersSymbol>& board)
{
	if((board.Num() > 0) && ((l_Width * l_Height) <= board.Num()))
	{
		TMap<int32, float> freeFields; // сюда будут добавляться все пустые поля с посчитанными оценками
		
		float priceCur = 0.0f;		// текущая цена в буффере
		float priceEqual = 1.f;	//цена, добавляемая за каждую фишку со своим символом
		float priceEnemy = 1.f;		// цена, добавляемая за каждую фишку соперника
		int32 query = 0;
		PlayersSymbol lastSym = PlayersSymbol::PSymb_None;
		
		// перебор по горизонтали вправо
		for(int32 y = 0; y < l_Height; y++)
		{
			priceCur = 0.0f;
			query = 0;
			for(int32 x = 0; x < l_Width; x++)
			{
				//Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y, l_Width, board);
				int32 currentNumber = y * l_Width + x; // номер, рассматриваемого тайла, на доске
		
				PlayersSymbol sym = board[currentNumber]; // символ на рассматриваемом тайле
				switch(sym)
				{
				case PlayersSymbol::PSymb_None: freeFields.Add(currentNumber, priceCur); priceCur = 0.0f; query = 0; break;
				default:
					if(lastSym == sym)	query++;
					else query = 1;
					if(Symbol == sym)
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEqual; // по такой формуле - чем длиннее череда фишек, тем больше внимания она привлекает
					}
					else
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEnemy;
					};
					break;
						
				}
			}
		}
		
		/*
		// перебор по горизонтали влево
		for(int32 y = 0; y < l_Height; y++)
		{
			priceCur = 0.0f;
			query = 0;
			for(int32 x = l_Width - 1; x >= 0; x--)
			{
				//Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y, l_Width, board);
				int32 currentNumber = y * l_Width + x; // номер, рассматриваемого тайла, на доске
		
				PlayersSymbol sym = board[currentNumber]; // символ на рассматриваемом тайле
				switch(sym)
				{
				case PlayersSymbol::PSymb_None: freeFields.Add(currentNumber, priceCur); priceCur = 0.0f; query = 0; break;
				default:
					if(lastSym == sym)	query++;
					else query = 1;
					if(Symbol == sym)
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEqual; // по такой формуле - чем длиннее череда фишек, тем больше внимания она привлекает
						//UE_LOG(LogTemp, Warning, TEXT("Price current: %f	Query: %f	Winline: %f"),priceCur, (float)query, static_cast<float>(WinLine));
						//priceCur += priceEqual;
					}
					else
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEnemy;
						//priceCur = priceEnemy;
					};
					break;
						
				}
			}
		}

		//перебор по вертикали вниз
		for(int32 x = 0; x < l_Width; x++)
		{
			priceCur = 0.0f;
			query = 0;
			for(int32 y = 0; y < l_Height; y++)
			{
				//Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y, l_Width, board);
				int32 currentNumber = y * l_Width + x; // номер, рассматриваемого тайла, на доске
		
				PlayersSymbol sym = board[currentNumber]; // символ на рассматриваемом тайле
				switch(sym)
				{
				case PlayersSymbol::PSymb_None: freeFields.Add(currentNumber, priceCur); priceCur = 0.0f; query = 0; break;
				default:
					if(lastSym == sym)	query++;
					else query = 1;
					if(Symbol == sym)
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEqual; // по такой формуле - чем длиннее череда фишек, тем больше внимания она привлекает
						//UE_LOG(LogTemp, Warning, TEXT("Price current: %f	Query: %f	Winline: %f"),priceCur, (float)query, static_cast<float>(WinLine));
						//priceCur += priceEqual;
					}
					else
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEnemy;
						//priceCur = priceEnemy;
					};
					break;
						
				}
			}
		}

		//перебор по вертикали вверх
		for(int32 x = 0; x < l_Width; x++)
		{
			priceCur = 0.0f;
			query = 0;
			for(int32 y = l_Height - 1; y >= 0; y--)
			{
				//Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y, l_Width, board);
				int32 currentNumber = y * l_Width + x; // номер, рассматриваемого тайла, на доске
		
				PlayersSymbol sym = board[currentNumber]; // символ на рассматриваемом тайле
				switch(sym)
				{
				case PlayersSymbol::PSymb_None: freeFields.Add(currentNumber, priceCur); priceCur = 0.0f; query = 0; break;
				default:
					if(lastSym == sym)	query++;
					else query = 1;
					if(Symbol == sym)
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEqual; // по такой формуле - чем длиннее череда фишек, тем больше внимания она привлекает
						//UE_LOG(LogTemp, Warning, TEXT("Price current: %f	Query: %f	Winline: %f"),priceCur, (float)query, static_cast<float>(WinLine));
						//priceCur += priceEqual;
					}
					else
					{
						priceCur += static_cast<float>(query)/static_cast<float>(WinLine) * priceEnemy;
						//priceCur = priceEnemy;
					};
					break;
						
				}
			}
		}
		*/

		/*
		// перебор по вертикали вниз
		for(int32 x = 0; x < l_Width; x++)
		{
			priceCur = 0.0f;
			for(int32 y = 0; y < l_Height; y++)
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y, l_Width, board);
			}
		}

		// перебор по вертикали вверх
		for(int32 x = 0; x < l_Width; x++)
		{
			priceCur = 0.0f;
			for(int32 y = l_Height - 1; y >= 0; y--)
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y, l_Width, board);
			}
		}*/

		
		// перебор по диагонали, опираясь на высоту
		
/*
		// / вверх с середины
		for(int32 y = l_Height - 1; y >= 0; y--)
		{
			priceCur = 0.0f;
			
			int32 y_current = y; // y, используемый для перебора для каждого х
			int32 x = 0; // текущий х
			while(((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0) && (y_current >= 0))
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y_current, l_Width, board);
				x++;
				y_current--;
			}
		}
		// \ вверх с середины
		for(int32 y = l_Height - 1; y >= 0; y--)
		{
			priceCur = 0.0f;
			
			int32 y_current = y;
			int32 x = l_Width - 1;
			while(((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0) && (x >= 0) && (y_current >= 0))
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y_current, l_Width, board);
				x--;
				y_current--;
			}
		}


		
		// \ вниз
		for(int32 y = 0; y < l_Height; y++)
		{
			priceCur = 0.0f;
			
			int32 y_current = y;
			int32 x = 0;
			while((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0)
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y_current, l_Width, board);
				x++;
				y_current++;
			}
		}
		// / вниз
		for(int32 y = 0; y < l_Height; y++)
		{
			priceCur = 0.0f;
			
			int32 y_current = y;
			int32 x = l_Width - 1;
			while(((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0) && (x >= 0))
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x, y_current, l_Width, board);
				x--;
				y_current++;
			}
		}


		// перебор по диагонали, опираясь на ширину

		// / влево
		for(int32 x = l_Width - 1; x >= 0; x--)
		{
			priceCur = 0.0f;
			
			int32 x_current = x;
			int32 y = 0;
			while(((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0) && (x_current >= 0))
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x_current, y, l_Width, board);
				x_current--;
				y++;
			}
		}
		// 
		for(int32 x = l_Width - 1; x >= 0; x--)
		{
			priceCur = 0.0f;
			
			int32 x_current = x;
			int32 y = l_Height - 1;
			while(((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0) && (x_current >= 0) && (y >= 0))
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x_current, y, l_Width, board);
				x_current--;
				y--;
			}
		}


		
		// 
		for(int32 x = 0; x < l_Width; x++)
		{
			priceCur = 0.0f;
			
			int32 x_current = x;
			int32 y = 0;
			while(((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0))
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x_current, y, l_Width, board);
				x_current++;
				y++;
			}
		}
		// 
		for(int32 x = 0; x < l_Width; x++)
		{
			priceCur = 0.0f;
			
			int32 x_current = x;
			int32 y = l_Height - 1;
			while(((y * l_Width + x) < board.Num() && (y * l_Width + x) >= 0) && (x_current >= 0))
			{
				Counter(freeFields, priceCur, priceEqual, priceEnemy, x_current, y, l_Width, board);
				x_current++;
				y--;
			}
		}



*/
		if(freeFields.Num() > 0)
		{
			float best = 0.f;
			for(auto a : freeFields)
			{
				if(a.Value > best) best = a.Value;

				UE_LOG(LogTemp, Warning, TEXT("Value: %d"),a.Value);
			}
			
			TArray<int32> keys;
			freeFields.GenerateKeyArray(keys);
			
			for(int32 a = keys.Num() - 1; a >= 0; a--)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Value: %d"),*freeFields.Find(keys[a]));
				if(*freeFields.Find(keys[a]) < best)
					freeFields.Remove(keys[a]);
			}

			keys.Empty();
			freeFields.GenerateKeyArray(keys);
			
			for(int32 a = keys.Num() - 1; a >= 0; a--)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Value: %d"),*freeFields.Find(keys[a]));
			}
			
			if(keys.Num() > 1)
			{
				int32 result = FMath::RandRange(0, keys.Num() - 1);
				return keys[result];
			}
			else
			{
				return keys[0];
			}
		}
		
	}


	return -1;
}

void AAAI_Middle_Summator::Counter(TMap<int32, float>& freeFields, float& priceCurrent, const float& priceEqual,
	const float& priceEnemy, const int32& X, const int32& Y, const int32& width, const TArray<PlayersSymbol>& board)
{
	int32 currentNumber = Y * width + X; // номер, рассматриваемого тайла, на доске
		
	PlayersSymbol sym = board[currentNumber]; // символ на на рассматриваемом тайле
	switch(sym)
	{
	case PlayersSymbol::PSymb_None: freeFields.Add(currentNumber, priceCurrent); priceCurrent = 0.0f; break;
	default:
		if(Symbol == sym)
		{
			priceCurrent += priceEqual;
		}
		else
		{
			priceCurrent = priceEnemy;
		};
		break;
						
	}
}
