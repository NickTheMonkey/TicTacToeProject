// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ABoard.h"
#include "DATA/FunctionLibraries/BPFL_General.h"
#include "Actors/ATile_Base.h"
#include "Components/AComp_BoardInfo.h"
#include "DATA/Interfaces/IPlayerController.h"

// Sets default values
AABoard::AABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boardInfo = CreateDefaultSubobject<UAComp_BoardInfo>(TEXT("Board info"));
	// TODO: этот бинд роняет проект (хз, почему)
	//boardInfo->WinnerFounded.BindUFunction(this, "WinnerIsFounded");
}

// Called when the game starts or when spawned
void AABoard::BeginPlay()
{
	Super::BeginPlay();

}

void AABoard::WinnerIsFounded(PlayersSymbol winner)
{
	IsWinnerFounded.ExecuteIfBound(winner);
}

// Called every frame
void AABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABoard::GetBoardStatus(int32& l_Width, int32& l_Height, TArray<PlayersSymbol>& l_Field)
{
	boardInfo->GetFieldStatus(l_Width, l_Height, l_Field);
}

void AABoard::SetTileStatus(const int32& l_TileNumber, const PlayersSymbol& l_NewSymbol)
{
	if(boardInfo->SetTileSymbolForNumber(l_TileNumber, l_NewSymbol))
	{
		Tiles[l_TileNumber]->SetSymbol(l_NewSymbol);

		AActor* turningActor = UBPFL_General::FindTurningController();
		if(turningActor)
		{
			if(turningActor->GetClass()->ImplementsInterface(UIPlayerController::StaticClass()))
			{
				IIPlayerController::Execute_NextPlayerTurn(turningActor);
			}
		}
	};
}

void AABoard::NewGame_Implementation(int32 field_Width, int32 field_Height, const int32& l_SymbolsInLineToWin)
{
	if(Tiles.Num()>0)
	{
		for(int32 a = 0; a < Tiles.Num(); a++)
		{
			Tiles[a]->OnTileClicked.Unbind();
			Tiles[a]->Destroy();
		}
		Tiles.Empty();
	}

	if(boardInfo->Initialization_Implementation(field_Width, field_Height, l_SymbolsInLineToWin))
	{
		TArray<PlayersSymbol> l_field;
		int32 w,h; // используются только для вызова следующей функции
		boardInfo->GetFieldStatus(w, h, l_field);
		
		const FVector l_Tile = TilesType.GetDefaultObject()->GetBounds(); // сохраняется размер тайла

		// место, откуда начнут спауниться тайлы с рассчетом на то, чтоб рут этого эктора находился по центру сгенерированного поля
		FVector spawnStart = { 0.f, 0.f, 0.f};
		spawnStart.X = static_cast<float>(field_Width - 1) * l_Tile.X * .5f;
		spawnStart.Y = static_cast<float>(field_Height - 1) * l_Tile.Y * .5f;
		
		if(l_field.Num() > 0)
		{
			for(int32 y = 0; y < field_Height; y++)
			{
				for(int32 x = 0; x < field_Width; x++)
				{
					FVector spawnLocation = GetActorLocation() - spawnStart;
					spawnLocation.X += static_cast<float>(x) * l_Tile.X;
					spawnLocation.Y += static_cast<float>(y) * l_Tile.Y;
					
					AATile_Base* createdTile = Cast<AATile_Base>(GetWorld()->SpawnActor(TilesType, &spawnLocation));
					int32 l_Number;
					if(boardInfo->Convert_Position_ToNumber(x,y,l_Number)) createdTile->SetTileNumber(l_Number);
					Tiles.Add(createdTile);

					createdTile->OnTileClicked.BindUFunction(this, "SetTileStatus");
				}
			}
		}
	}
}

