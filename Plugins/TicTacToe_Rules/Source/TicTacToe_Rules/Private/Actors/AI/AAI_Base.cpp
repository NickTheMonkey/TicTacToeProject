// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AI/AAI_Base.h"

// Sets default values
AAAI_Base::AAAI_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAAI_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAI_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


#pragma region PlayerControllerInterface

bool AAAI_Base::GetSymbol_Implementation(PlayersSymbol& l_Symbol)
{
	l_Symbol = Symbol;
	return true;
}

void AAAI_Base::SetSymbol_Implementation(const PlayersSymbol& l_Symbol)
{
	Symbol = l_Symbol;
}

void AAAI_Base::SetNextPlayerReference_Implementation(AActor* l_NextPlayer)
{
	NextPlayer = l_NextPlayer;
}

void AAAI_Base::Turn_Begin_Implementation()
{
	isTurning = true;
}

void AAAI_Base::Turn_End_Implementation()
{
	isTurning = false;
}

bool AAAI_Base::GetIsTurningController_Implementation()
{
	return isTurning;
}

void AAAI_Base::NextPlayerTurn_Implementation()
{
	if(NextPlayer)
	{
		if(NextPlayer->GetClass()->ImplementsInterface(UIPlayerController::StaticClass()))
		{
			Turn_End();
			IIPlayerController::Execute_Turn_Begin(NextPlayer);
		}
	}
}

#pragma endregion PlayerControllerInterface