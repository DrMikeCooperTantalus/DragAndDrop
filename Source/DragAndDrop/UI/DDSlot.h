// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

class IDDContainer
{
public:
	virtual bool CanDrop(class UDDSlot* slot, class URPGObject* obj) = 0;
	virtual void Drop(class UDDSlot* slot, class URPGObject* obj) = 0;
};

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

	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	int Index;
	class IDDContainer* ParentContainer;

	void SetObject(class URPGObject* obj);
	bool CanDrop(class URPGObject* obj);
};
