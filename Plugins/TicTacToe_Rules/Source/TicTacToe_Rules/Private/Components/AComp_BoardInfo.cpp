// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AComp_BoardInfo.h"

#include "DATA/Interfaces/IPlayerController.h"		// ����� ��� ������� 
#include "Kismet/GameplayStatics.h"					// � ��������� ���� ������� ������� ����������

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
	int32 l_position; // ����� ��������������� �������
	if(Convert_Position_ToNumber(x,y, l_position))
	{
		PlayersSymbol l_buffer = Field[l_position]; // ������, ������� ��������� �� ��������������� �����������
			
		
		
		if((l_buffer == PlayersSymbol::PSymb_None) || (l_buffer == PlayersSymbol::PSymb_Count)) // Symb_Count �� ������� ��������� �������������� �� �����. �������� ��� �������������
			{
			counter = 0;
			return;
			}
		if(l_buffer == currentSymbol) // ������� ������ ����� ��� �� ������, ��� � ����������
			{
			counter++;
			}
		if(l_buffer != currentSymbol)
		{
			counter = 1; // 1 ������ ��� � ���� �������� �� ���������� None, � ������ ������ �������� �������, � ������� ������ ����������� ������
			currentSymbol = l_buffer;
		}

		if(counter >= SymbolsInLineForWin)
		{
			// ���� � ����� ��������, �� ������������ ABoard, ������ ������, ������� ����������� �������� ���� �������
			WinnerFounded.ExecuteIfBound(currentSymbol);

			//�������
			TArray<AActor*> actors;
			UGameplayStatics::GetAllActorsWithInterface(GWorld, UIPlayerController::StaticClass(), actors);
			for(AActor* a: actors)
			{
				IIPlayerController::Execute_ShowWinner(a, currentSymbol);
			}
		}

		// ���� �� ���� �� �������� ��������� ������ - ����� ��������� "�����"
		if(!Field.Contains(PlayersSymbol::PSymb_None))
		{
			TArray<AActor*> actors;
			UGameplayStatics::GetAllActorsWithInterface(GWorld, UIPlayerController::StaticClass(), actors);
			for(AActor* a: actors)
			{
				IIPlayerController::Execute_ShowWinner(a, PlayersSymbol::PSymb_None);
			}
		}
	};
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

	UE_LOG(LogTemp, Log, TEXT("Requested position is not valid"));
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

	UE_LOG(LogTemp, Log, TEXT("Field have not tile number %d"), position);
	return false;
}

bool UAComp_BoardInfo::SetTileSymbolForNumber(const int32& l_Number, const PlayersSymbol& l_Symbol)
{
	if(!Field.IsValidIndex(l_Number)) return false;

	Field[l_Number] = l_Symbol;
	CheckWinner();
	return true;
}

void UAComp_BoardInfo::GetFieldStatus(TArray<PlayersSymbol>& l_Field)
{
	l_Field = Field;
}

bool UAComp_BoardInfo::Convert_Number_ToPosition(const int32& l_Number, int32& l_Width, int32& l_Height)
{	
	l_Width = l_Number%Width;		// ��������� ������ - ������� ������� ��������� ������
	l_Height = l_Number/Width;		// ��������, ���� Width = 10, �� l_Number = 10 �������� ������ �������� ������ ������
	return true;
}

bool UAComp_BoardInfo::Convert_Position_ToNumber(const int32& l_Width, const int32& l_Height, int32& l_Number)
{
	l_Number = l_Height * Width + l_Width;
	if(l_Number >= Field.Num())
	{
		//UE_LOG(LogTemp, Log, TEXT("Required position grater than field size"));
		return false;
	}
	return true;
}

void UAComp_BoardInfo::CheckWinner_Implementation()
{
	int32 l_count = 0; // ������� ���������� ��������, ������������� ������
	PlayersSymbol l_sym = PlayersSymbol::PSymb_None; // ��� ���������� ���������������� �������

	// ������� �� �����������
	for(int32 y = 0; y < Height; y++)
	{
		for(int32 x = 0; x < Width; x++)
		{
			Counter(x,y,l_sym,l_count);
		}
		l_count = 0;
	}

	// ������� �� ���������
	for(int32 x = 0; x < Width; x++)
	{
		for(int32 y = 0; y < Height; y++)
		{
			Counter(x,y,l_sym,l_count);
		}
		l_count = 0;
	}
	// ������� �� ��������� ��������� (\), ������� � ������ ������� ����, ���������� �� y == 0
	for(int32 y = Height - 1; y >= 0; y--)
	{
			int32 y_current = y; // y, ������������ ��� �������� ��� ������� �
			int32 x = 0; // ������� �
			int32 l_position; // ����� ��������������� �������
			l_count = 0;
			while(Convert_Position_ToNumber(x,y_current, l_position))
			{
				Counter(x,y_current,l_sym,l_count);
				x++;
				y_current++;
			}
		l_count = 0;
	}
	// ������� �� ��������� ��������� (\), ������� � ������ �������� ����,�������� ������ �� x == Width
	for(int32 x = 0; x < Width; x++)
	{
		int32 x_current = x; // x, ������������ ��� �������� ��� ������� y
		int32 y = 0; // ������� y
		int32 l_position; // ����� ��������������� �������
		l_count = 0;
		while(Convert_Position_ToNumber(x_current,y, l_position))
		{
			Counter(x_current,y,l_sym,l_count);
			x_current++;
			y++;
		}
		l_count = 0;
	}
	// ������� �� ������������� ��������� (/), ������� � ������� ������� ����,�������� ����� �� y == 0
	for(int32 y = Height - 1; y >= 0; y--)
	{
		int32 y_current = y; // y, ������������ ��� �������� ��� ������� x
		int32 x = Width; // ������� x
		int32 l_position; // ����� ��������������� �������
		l_count = 0;
		while(Convert_Position_ToNumber(x,y_current, l_position))
		{
			Counter(x,y_current,l_sym,l_count);
			x--;
			y_current++;
		}
		l_count = 0;
	}
	// ������� �� ������������� ��������� (/), ������� � ������� �������� ����,�������� ����� �� � == 0
	for(int32 x = Width - 1; x >= 0; x--)
	{
		int32 x_current = x; // x, ������������ ��� �������� ��� ������� y
		int32 y = 0; // ������� y
		int32 l_position; // ����� ��������������� �������
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
	// �������� �������� �������� ����. ���� ������ ��� ������ ������ ������� - ��� ����������� �� 1. �.�. ��������� ����, ��� ������ ����������, ������� :)
	if(l_Width < 1)
	{
		l_Width = 1;
		UE_LOG(LogTemp, Log, TEXT("Width was initiate less than 1. Width set to %d"), l_Width);
	}
	if(l_Height < 1)
	{
		l_Height = 1;
		UE_LOG(LogTemp, Log, TEXT("Height was initiate less than 1. Height set to %d"), l_Height);
	}
	Width = l_Width;
	Height = l_Height;

	
	// ������������� �����, ������������ �� ����������� ���-�� ��������, ������� ����� ��������� � ���, ��� ������
	if((l_SymbolsInLineToWin > l_Width) && (l_SymbolsInLineToWin > l_Height)) // ���� ���������� �������� �������� �������� ����� � ��������� ����
	{
		SymbolsInLineForWin = (l_Width < l_Height ? l_Width : l_Height);
		UE_LOG(LogTemp, Log, TEXT("Symbols number in line to win greater than any side. This value set to %d"), SymbolsInLineForWin);
	}
	else
	{
		SymbolsInLineForWin = l_SymbolsInLineToWin;
	};

	// ��������� ����
	if(Field.Num() > 0) Field.Empty();		// ������� ������ � �������� � ������, ���� �� �� ������
	Field.Init(PlayersSymbol::PSymb_None, l_Width*l_Height);	// ������������� ������� � ���������� ������
	
	return true;
}

