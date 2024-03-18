// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragAndDrop/UI/DDSlot.h"
#include "RPGEquipScreen.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API URPGEquipScreen : public UUserWidget, public IDDContainer
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UDDSlot* HelmetSlot;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UDDSlot* WeaponSlot;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UDDSlot* ScrollSlot;

	virtual bool CanDrop(class UDDSlot* slot, class URPGObject* obj) override;
	virtual void Drop(class UDDSlot* slot, class URPGObject* obj) override;
	virtual bool IsReadOnly() override { return false; }
	
	virtual void NativeConstruct() override;
	
	void SetCharacter(class ADragAndDropCharacter* ch);
	
protected:
	class ADragAndDropCharacter* Character;
};
