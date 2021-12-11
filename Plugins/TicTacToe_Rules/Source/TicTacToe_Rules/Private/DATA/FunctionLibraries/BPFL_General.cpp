// Fill out your copyright notice in the Description page of Project Settings.


#include "DATA/FunctionLibraries/BPFL_General.h"
#include "DATA/Interfaces/IPlayerController.h"
#include "Kismet/GameplayStatics.h"

AActor* UBPFL_General::GetControllerWithSymbol(const PlayersSymbol& l_Symbol)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, UIPlayerController::StaticClass(), actors);

	if(actors.Num() > 0)
	{
		for(int a = 0; a < actors.Num(); a++)
		{
			PlayersSymbol l_sym;
			IIPlayerController::Execute_GetSymbol(actors[a], l_sym);
			if(l_sym == l_Symbol) return actors[a];
		}
	}

	return nullptr;
}

AActor* UBPFL_General::FindTurningController()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, UIPlayerController::StaticClass(), actors);

	if(actors.Num() > 0)
	{
		for(int a = 0; a < actors.Num(); a++)
		{
			if(IIPlayerController::Execute_GetIsTurningController(actors[a]))
			{
				return actors[a];
			}
		}
	}

	return nullptr;
}
