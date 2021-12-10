// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATile_Base.generated.h"

DECLARE_DELEGATE_OneParam(FOnTileClicked, int32);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnTileClicked OnTileClicked;
	
	UFUNCTION(BlueprintNativeEvent)
	void Event_Click();

	UFUNCTION(BlueprintCallable)
	void SetTileNumber(const int32 Number);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetTileNumber();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetBounds();
};
