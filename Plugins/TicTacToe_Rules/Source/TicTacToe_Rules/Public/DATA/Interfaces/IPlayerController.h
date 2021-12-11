// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DATA/Enums/ENUMS.h"
#include "IPlayerController.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UIPlayerController : public UInterface
{
	GENERATED_BODY()
	
};

class TICTACTOE_RULES_API IIPlayerController
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetSymbol(PlayersSymbol& l_Symbol);

	// вначале игры каждому игроку назначается его символ
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetSymbol(const PlayersSymbol& l_Symbol);

	// ссылка на следующего игрока (используется для передачи хода)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetNextPlayerReference(AActor* l_NextPlayer);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (Tooltip = "Function for open player to turn"))
	void Turn_Begin();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (Tooltip = "Function for close player to turn"))
	void Turn_End();
	//является ли эктор, в данный момент, ходящим
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsTurningController();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NextPlayerTurn();
};
