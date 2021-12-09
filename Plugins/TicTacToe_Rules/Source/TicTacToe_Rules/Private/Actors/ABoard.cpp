// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ABoard.h"
#include "Actors/ATile_Base.h"
#include "Components/AComp_BoardInfo.h"

// Sets default values
AABoard::AABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boardInfo->CreateDefaultSubobject<UAComp_BoardInfo>("Board info");
}

// Called when the game starts or when spawned
void AABoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABoard::NewGame_Implementation(int32 field_Width, int32 field_Height, const int32& l_SymbolsInLineToWin)
{
	if(Tiles.Num()>0)
	{
		for(int32 a = 0; a < Tiles.Num(); a++)
		{
			Tiles[a]->Destroy();
		}
		Tiles.Empty();
	}

	if(boardInfo->Initialization_Implementation(field_Width, field_Height, l_SymbolsInLineToWin))
	{
		TArray<PlayersSymbol> l_field;
		boardInfo->GetFieldStatus(l_field);
		
		const FVector l_Tile = TilesType.GetDefaultObject()->GetBounds();
		const float l_DistanceBetween = DistanceBetweenTiles * .5f; //делится на два, потому что находящиеся рядом тайлы буду отступать друг от друга на заданное здесь расстояние. Если каждый будет отступать на указанное, дизайнером, расстояние, то промежуточное, фактически, будет вдвое больше
		if(l_field.Num() > 0)
		{
			for(int y = 0; y < field_Height; y++)
			{
				for(int x = 0; x < field_Width; x++)
				{
					FVector spawnLocation = GetActorLocation();
					spawnLocation.X += x * l_Tile.X + l_DistanceBetween;
					spawnLocation.Y += y * l_Tile.Y + l_DistanceBetween;
					AATile_Base* createdTile = GetWorld()->SpawnActor<AATile_Base>(spawnLocation,FRotator(0,0,0));
					int32 l_Number;
					if(boardInfo->Convert_Position_ToNumber(x,y,l_Number)) createdTile->SetTileNumber(l_Number);
				}
			}
		}
	}
}

