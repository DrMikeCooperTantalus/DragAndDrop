// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ERPGItemType : uint8
{
	None = 0 UMETA(Hidden),
	Potion = 1,
	Helmet = 2,
	Weapon = 4,
	Scroll = 8
};

#include "RPGObject.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API URPGObject : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ERPGItemType> ItemType;
};
