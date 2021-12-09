// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DATA/Enums/ENUMS.h"

#include "AComp_BoardInfo.generated.h"
DECLARE_DELEGATE_OneParam(FWinnerFounded, PlayersSymbol);

UCLASS( ClassGroup=(Board), meta=(BlueprintSpawnableComponent) )
class TICTACTOE_RULES_API UAComp_BoardInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAComp_BoardInfo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Counter(const int32& x, const int32& y, PlayersSymbol& currentSymbol, int32& counter);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FWinnerFounded WinnerFounded;
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	bool GetTileSymbol(const int32& l_Width, const int32& l_Height, PlayersSymbol& symbol);
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	bool SetTileSymbol(const int32& l_Width, const int32& l_Height, const PlayersSymbol& l_Symbol);
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void GetFieldStatus(TArray<PlayersSymbol>& l_Field);

	// конвертирует номер в положение тайла на доске
	UFUNCTION(BlueprintCallable)
	bool Convert_Number_ToPosition(const int32& l_Number, int32& l_Width, int32& l_Height);
	// конвертирует положение тайла на доске в номер
	UFUNCTION(BlueprintCallable)
	bool Convert_Position_ToNumber(const int32& l_Width, const int32& l_Height, int32& l_Number);
protected:
	// Возможность управления переменными из принтов оставлена на случай, если игра будет дорабатываться дизайнерами
	// ширина игрового поля
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field")
	int32 Width;
	// высота игрополя
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field")
	int32 Height;
	// содержимое клеток игрополя
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Field")
	TArray<PlayersSymbol> Field;

	// кол-во символов, которое необходимо выстроить подряд для того, чтоб победить
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
	int32 SymbolsInLineForWin;
	
	UFUNCTION(BlueprintNativeEvent)
	bool Initialization(int32 l_Width, int32 l_Height, const int32& l_SymbolsInLineToWin);

	UFUNCTION(BlueprintNativeEvent)
	void CheckWinner();
};