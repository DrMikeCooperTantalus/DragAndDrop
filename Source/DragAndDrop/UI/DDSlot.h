// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDSlot.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API UDDSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class URPGObjectUI* Object;
};
