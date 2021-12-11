// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DATA/Enums/ENUMS.h"
#include "GameFramework/Actor.h"
#include "ATile_Base.generated.h"

DECLARE_DELEGATE_TwoParams(FOnTileClicked, int32, PlayersSymbol);

UCLASS()
class TICTACTOE_RULES_API AATile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATile_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnClick(UPrimitiveComponent* ClickedActor, FKey ButtonPressed);

	UPROPERTY()
	int32 TileNumber = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Tooltip = "Mesh for set size"))
	UStaticMeshComponent* SizeMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnTileClicked OnTileClicked;
	
	UFUNCTION(BlueprintCallable)
	void SetTileNumber(const int32 Number);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetTileNumber();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetBounds();

	UFUNCTION(BlueprintNativeEvent, meta = (Tooltip = "Visual effect for change symbol"))
	void SetSymbol(const PlayersSymbol& l_Sym);

};
