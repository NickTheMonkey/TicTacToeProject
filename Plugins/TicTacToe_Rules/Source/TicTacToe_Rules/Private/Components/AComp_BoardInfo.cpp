// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AComp_BoardInfo.h"

// Sets default values for this component's properties
UAComp_BoardInfo::UAComp_BoardInfo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAComp_BoardInfo::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAComp_BoardInfo::Counter(const int32& x, const int32& y, PlayersSymbol& currentSymbol, int32& counter)
{
	int32 l_position; // номер рассматриваемой позиции
	Convert_Position_ToNumber(x,y, l_position);
	PlayersSymbol l_buffer = Field[l_position]; // символ, который находится по рассматриваемым координатам
			
	if((l_buffer == PlayersSymbol::PSymb_None) || (l_buffer == PlayersSymbol::PSymb_Count)) // Symb_Count не подлжен оказаться использованным на доске. Добавлен для перестраховки
		{
		counter = 0;
		return;
		}
	if(l_buffer == currentSymbol) // текущая клетка имеет тот же символ, что и предыдущая
		{
		counter++;
		}
	if(l_buffer != currentSymbol)
	{
		counter = 1; // 1 потому что в этой проверке не учавствует None, а значит символ является игроком, и счетчик теперь считывается отсюда
		currentSymbol = l_buffer;
	}

	if(counter >= SymbolsInLineForWin)
	{
		WinnerFounded.Execute(currentSymbol);
		return;
	}
}


// Called every frame
void UAComp_BoardInfo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UAComp_BoardInfo::GetTileSymbol(const int32& l_Width, const int32& l_Height, PlayersSymbol& symbol)
{
	int32 position;
	Convert_Position_ToNumber(l_Width, l_Height, position);
	if(Field.IsValidIndex(position))
	{
		symbol = Field[position];
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Requested position is not valid"));
	return false;
}

bool UAComp_BoardInfo::SetTileSymbol(const int32& l_Width, const int32& l_Height, const PlayersSymbol& l_Symbol)
{
	int32 position;
	if(Convert_Position_ToNumber(l_Width, l_Height, position))
	{
		Field[position] = l_Symbol;
		CheckWinner();
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Field have not tile number %d"), position);
	return false;
}

void UAComp_BoardInfo::GetFieldStatus(TArray<PlayersSymbol>& l_Field)
{
	l_Field = Field;
}

bool UAComp_BoardInfo::Convert_Number_ToPosition(const int32& l_Number, int32& l_Width, int32& l_Height)
{	
	l_Width = l_Number%Width;		// кратность ширины - нулевой элемент следующей строки
	l_Height = l_Number/Width;		// например, если Width = 10, то l_Number = 10 является первым символом второй строки
	return true;
}

bool UAComp_BoardInfo::Convert_Position_ToNumber(const int32& l_Width, const int32& l_Height, int32& l_Number)
{
	l_Number = l_Height * Width + l_Width;
	if(l_Number > Field.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Required position grater than field size"));
		return false;
	}
	return true;
}

void UAComp_BoardInfo::CheckWinner_Implementation()
{
	int32 l_count = 0; // счетчик одинаковых символов, расположенных подряд
	PlayersSymbol l_sym = PlayersSymbol::PSymb_None; // тип последнего рассматриваемого символа

	// перебор по горизонтали
	for(int32 y = 0; y < Height; y++)
	{
		for(int32 x = 0; x < Width; x++)
		{
			Counter(x,y,l_sym,l_count);
			/*int32 l_position; // номер рассматриваемой позиции
			Convert_Position_ToNumber(x,y, l_position);
			PlayersSymbol l_buffer = Field[l_position]; // символ, который находится по рассматриваемым координатам
			
			if((l_buffer == PlayersSymbol::PSymb_None) || (l_buffer == PlayersSymbol::PSymb_Count)) // Symb_Count не подлжен оказаться использованным на доске. Добавлен для перестраховки
			{
				l_count = 0;
				continue;
			}
			if(l_buffer == l_sym) // текущая клетка имеет тот же символ, что и предыдущая
			{
				l_count++;
			}
			if(l_buffer != l_sym)
			{
				l_count = 1; // 1 потому что в этой проверке не учавствует None, а значит символ является игроком, и счетчик теперь считывается отсюда
				l_sym = l_buffer;
			}

			if(l_count >= SymbolsInLineForWin)
			{
				FoundedWinner(l_sym);
				return;
			}*/
		}
	}

	// перебор по вертикали
	for(int32 x = 0; x < Width; x++)
	{
		for(int32 y = 0; y < Height; y++)
		{
			Counter(x,y,l_sym,l_count);
		}
	}

	// перебор по спадающей диагонали (\), начиная с левого нижнего угла, поднимаясь до y == 0
	for(int32 y = Height - 1; y >= 0; y--)
	{
			int32 y_current = y; // y, используемый для перебора для каждого х
			int32 x = 0; // текущий х
			int32 l_position; // номер рассматриваемой позиции
			l_count = 0;
			while(Convert_Position_ToNumber(x,y_current, l_position))
			{
				Counter(x,y_current,l_sym,l_count);
				x++;
				y_current++;
			}
	}

	// перебор по спадающей диагонали (\), начиная с левого верхнего угла,двигаясь вправо до x == Width
	for(int32 x = 0; x < Width; x++)
	{
		int32 x_current = x; // x, используемый для перебора для каждого y
		int32 y = 0; // текущий y
		int32 l_position; // номер рассматриваемой позиции
		l_count = 0;
		while(Convert_Position_ToNumber(x_current,y, l_position))
		{
			Counter(x_current,y,l_sym,l_count);
			x_current++;
			y++;
		}
	}

	// перебор по поднимающейся диагонали (/), начиная с правого нижнего угла,двигаясь вверх до y == 0
	for(int32 y = Height - 1; y >= 0; y--)
	{
		int32 y_current = y; // y, используемый для перебора для каждого x
		int32 x = Width; // текущий x
		int32 l_position; // номер рассматриваемой позиции
		l_count = 0;
		while(Convert_Position_ToNumber(x,y_current, l_position))
		{
			Counter(x,y_current,l_sym,l_count);
			x--;
			y_current++;
		}
	}

	// перебор по поднимающейся диагонали (/), начиная с правого верхнего угла,двигаясь влево до х == 0
	for(int32 x = Width - 1; x >= 0; x--)
	{
		int32 x_current = x; // x, используемый для перебора для каждого y
		int32 y = 0; // текущий y
		int32 l_position; // номер рассматриваемой позиции
		l_count = 0;
		while(Convert_Position_ToNumber(x_current,y, l_position))
		{
			Counter(x_current,y,l_sym,l_count);
			x_current--;
			y++;
		}
	}
}

bool UAComp_BoardInfo::Initialization_Implementation(int32 l_Width, int32 l_Height, const int32& l_SymbolsInLineToWin)
{
	// проверка заданных размеров поля. Если высота или ширина меньше единицы - они установятся на 1. Т.е. получится поле, где первый походивший, победит :)
	if(l_Width < 1)
	{
		l_Width = 1;
		UE_LOG(LogTemp, Warning, TEXT("Width was initiate less than 1. Width set to %d"), l_Width);
	}
	if(l_Height < 1)
	{
		l_Height = 1;
		UE_LOG(LogTemp, Warning, TEXT("Height was initiate less than 1. Height set to %d"), l_Height);
	}
	Width = l_Width;
	Height = l_Height;

	
	// инициализация числа, указывающего на необходимое кол-во символов, которое нужно выстроить в ряд, для победы
	if((l_SymbolsInLineToWin > l_Width) && (l_SymbolsInLineToWin > l_Height)) // если невозможно впихнуть заданную победную линию в созданное поле
	{
		SymbolsInLineForWin = (l_Width < l_Height ? l_Width : l_Height);
		UE_LOG(LogTemp, Warning, TEXT("Symbols number in line to win greater than any side. This value set to %d"), SymbolsInLineForWin);
	}
	else
	{
		SymbolsInLineForWin = l_SymbolsInLineToWin;
	};

	// генерация поля
	if(Field.Num() > 0) Field.Empty();		// очищаем массив с клетками в случае, если он не пустой
	Field.Init(PlayersSymbol::PSymb_None, l_Width*l_Height);	// инициализация массива с содержимым клеток
	
	return true;
}

