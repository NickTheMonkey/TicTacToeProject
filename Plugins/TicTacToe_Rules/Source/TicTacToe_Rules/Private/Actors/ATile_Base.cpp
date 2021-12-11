// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/ATile_Base.h"
#include "DATA/FunctionLibraries/BPFL_General.h"
#include "DATA/Interfaces/IPlayerController.h"

// Sets default values
AATile_Base::AATile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SizeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SizeMesh"));

	RootComponent = Root;	
	SizeMesh->SetupAttachment(Root);
	
	SizeMesh->OnClicked.AddDynamic(this, &AATile_Base::OnClick);
	SizeMesh->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AATile_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AATile_Base::OnClick_Implementation(UPrimitiveComponent* ClickedActor, FKey ButtonPressed)
{
	AActor* l_Controller = UBPFL_General::FindTurningController(); // поиск ходящего игрока, чтоб получить его символ
	if(l_Controller)
	{
		if(l_Controller->GetClass()->ImplementsInterface(UIPlayerController::StaticClass()))
		{
			PlayersSymbol l_Sym;
			if(IIPlayerController::Execute_GetSymbol(l_Controller, l_Sym))
			{
				SetSymbol(l_Sym); // символ найденного игрока дается тайлу
				OnTileClicked.ExecuteIfBound(TileNumber, l_Sym);
			};

			IIPlayerController::Execute_NextPlayerTurn(l_Controller);
		};
	};
}

void AATile_Base::SetSymbol_Implementation(const PlayersSymbol& l_Sym)
{
	
}

// Called every frame
void AATile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AATile_Base::SetTileNumber(const int32 Number)
{
	TileNumber = Number;
}

int32 AATile_Base::GetTileNumber()
{
	return TileNumber;
}

FVector AATile_Base::GetBounds()
{
	FVector meshBoundsMin = {0.f,0.f,0.f};
	FVector meshBoundsMax = {0.f,0.f,0.f};;
	if(SizeMesh)
	{
		SizeMesh->GetLocalBounds(meshBoundsMin, meshBoundsMax);
		meshBoundsMax -= meshBoundsMin;		//получим реальный размер тайла (меша)
	}
	return meshBoundsMax;
}

