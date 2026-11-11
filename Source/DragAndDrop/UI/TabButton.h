// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TabButton.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API UTabButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Name;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* Select;

	virtual void NativeConstruct();

	void Init(FString& name, class UTabs* parent);

	const FString& GetTabName() { return TabName; }

	void ShowSelect(bool On);

protected:

	UFUNCTION()
	void OnClicked();

	FString TabName;
	class UTabs* ParentTabs;

	bool Selected = false;
};
