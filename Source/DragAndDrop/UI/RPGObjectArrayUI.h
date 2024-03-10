// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGObjectArrayUI.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API URPGObjectArrayUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class URPGObject*> Objects;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UPanelWidget* Container;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UDDSlot* Prefab;

	virtual void NativeConstruct() override;

	void CreateSlots();
};