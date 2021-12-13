// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DATA/Interfaces/IPlayerController.h"
#include "GameFramework/Actor.h"
#include "AAI_Base.generated.h"

class AABoard;

UCLASS()
class TICTACTOE_RULES_API AAAI_Base : public AActor, public IIPlayerController
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAI_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	PlayersSymbol Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* NextPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isTurning;
	UPROPERTY()
	AABoard* BoardReference;

	// функция, в которой будет находиться алгоритм рассчета хода
	virtual int32 CalculateTurn(const int32& l_Width, const int32& l_Height, const TArray<PlayersSymbol>& board);

	// линия, которую нужно собрать, для победы
	int32 WinLine;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
#pragma region PlayerControllerInterface
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetSymbol(PlayersSymbol& l_Symbol);
	virtual bool GetSymbol_Implementation(PlayersSymbol& l_Symbol) override;

	// вначале игры каждому игроку назначается его символ
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetSymbol(const PlayersSymbol& l_Symbol);
	virtual void SetSymbol_Implementation(const PlayersSymbol& l_Symbol) override;

	// ссылка на следующего игрока (используется для передачи хода)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetNextPlayerReference(AActor* l_NextPlayer);
	virtual void SetNextPlayerReference_Implementation(AActor* l_NextPlayer) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (Tooltip = "Function for open player to turn"))
	void Turn_Begin();
	virtual void Turn_Begin_Implementation() override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (Tooltip = "Function for open player to turn"))
	void Turn_End();
	virtual void Turn_End_Implementation() override;
	//является ли эктор, в данный момент, ходящим
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsTurningController();
	virtual bool GetIsTurningController_Implementation() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NextPlayerTurn();
	virtual void NextPlayerTurn_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetBoardReference(AABoard* boardRef);
	virtual void SetBoardReference_Implementation(AABoard* boardRef) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowWinner(PlayersSymbol winnner);
	virtual void ShowWinner_Implementation(PlayersSymbol winnner) override;

#pragma endregion PlayerControllerInterface
};
