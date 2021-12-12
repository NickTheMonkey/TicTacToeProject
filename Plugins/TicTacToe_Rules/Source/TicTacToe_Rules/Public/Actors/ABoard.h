// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DATA/Enums/ENUMS.h"
#include "GameFramework/Actor.h"
#include "ABoard.generated.h"

class UAComp_BoardInfo;
class AATile_Base;

DECLARE_DELEGATE_OneParam(FIsWinnerFounded, PlayersSymbol);

UCLASS()
class TICTACTOE_RULES_API AABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AATile_Base*> Tiles;

	// тип тайлов, которые будут генерироваться на поле во время инициализации
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AATile_Base> TilesType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAComp_BoardInfo* boardInfo;

	void WinnerIsFounded(PlayersSymbol winner);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FIsWinnerFounded IsWinnerFounded;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NewGame(int32 field_Width, int32 field_Height, const int32& l_SymbolsInLineToWin);

	// функции для ИИ
	UFUNCTION(BlueprintCallable)
	void GetBoardStatus(TArray<PlayersSymbol>& l_Field);
	UFUNCTION(BlueprintCallable)
	void SetTileStatus(const int32& l_TileNumber, const PlayersSymbol& l_NewSymbol);
};
