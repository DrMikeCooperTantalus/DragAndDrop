// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragAndDrop/RPGObject.h"
#include "DragAndDrop/UI/DDSlot.h"
#include "RPGObjectArrayUI.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API URPGObjectArrayUI : public UUserWidget, public IDDContainer
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UPanelWidget* Container;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UDDSlot* Prefab;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ERPGItemType"))
	uint8 AllowedTypes;

	// set this to true to have an array that does not get modified, eg a palette
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ReadOnly = false;
	
	void SetObjects(TArray<class URPGObject*>* objects);
	TArray<class URPGObject*>* GetObjectsArray() { return Objects; }

	virtual bool CanDrop(class UDDSlot* slot, class URPGObject* obj) override;
	virtual void Drop(class UDDSlot* slot, class URPGObject* obj) override;
	virtual bool IsReadOnly() override { return ReadOnly; }
	
protected:
	void CreateSlots();

	TArray<class URPGObject*>* Objects;
};
