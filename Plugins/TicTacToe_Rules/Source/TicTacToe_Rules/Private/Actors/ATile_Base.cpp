// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/ATile_Base.h"

// Sets default values
AATile_Base::AATile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = Root;	
	SMesh->SetupAttachment(Root);
	
	SMesh->OnClicked.AddDynamic(this, &AATile_Base::OnClick);
}

// Called when the game starts or when spawned
void AATile_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AATile_Base::OnClick_Implementation(UPrimitiveComponent* ClickedActor, FKey ButtonPressed)
{
	Event_Click();
}

// Called every frame
void AATile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AATile_Base::Event_Click_Implementation()
{
	OnTileClicked.ExecuteIfBound(TileNumber);
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
	if(SMesh)
	{
		SMesh->GetLocalBounds(meshBoundsMin, meshBoundsMax);
		meshBoundsMax -= meshBoundsMin;		//получим реальный размер тайла (меша)
	}
	return meshBoundsMax;
}

