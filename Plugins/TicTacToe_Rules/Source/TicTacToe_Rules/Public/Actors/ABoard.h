// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABoard.generated.h"

class UAComp_BoardInfo;
class AATile_Base;

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

	UPROPERTY()
	UAComp_BoardInfo* boardInfo;

	TArray<AATile_Base*> Tiles;

	// ��� ������, ������� ����� �������������� �� ���� �� ����� �������������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<AATile_Base> TilesType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NewGame(int32 field_Width, int32 field_Height, const int32& l_SymbolsInLineToWin);

	// ��������� ����� �������
	UPROPERTY(EditAnywhere)
	float DistanceBetweenTiles = 10.f;

};
