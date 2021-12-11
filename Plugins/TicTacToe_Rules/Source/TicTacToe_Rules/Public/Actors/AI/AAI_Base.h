// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DATA/Interfaces/IPlayerController.h"
#include "GameFramework/Actor.h"
#include "AAI_Base.generated.h"

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
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region PlayerControllerInterface
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetSymbol(PlayersSymbol& l_Symbol);
	virtual bool GetSymbol_Implementation(PlayersSymbol& l_Symbol) override;

	// ������� ���� ������� ������ ����������� ��� ������
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetSymbol(const PlayersSymbol& l_Symbol);
	virtual void SetSymbol_Implementation(const PlayersSymbol& l_Symbol) override;

	// ������ �� ���������� ������ (������������ ��� �������� ����)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetNextPlayerReference(AActor* l_NextPlayer);
	virtual void SetNextPlayerReference_Implementation(AActor* l_NextPlayer) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (Tooltip = "Function for open player to turn"))
	void Turn_Begin();
	virtual void Turn_Begin_Implementation() override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (Tooltip = "Function for open player to turn"))
	void Turn_End();
	virtual void Turn_End_Implementation() override;
	//�������� �� �����, � ������ ������, �������
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsTurningController();
	virtual bool GetIsTurningController_Implementation() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NextPlayerTurn();
	virtual void NextPlayerTurn_Implementation() override;

#pragma endregion PlayerControllerInterface
};