// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGObjectUI.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API URPGObjectUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* Icon;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Name;

	void SetObject(class URPGObject* obj);
	class URPGObject* GetObj() const { return Obj; }

	class UDDSlot* ParentSlot;
	
protected:
	class URPGObject* Obj;
};
