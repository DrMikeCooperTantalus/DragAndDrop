// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tabs.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API UTabs : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UPanelWidget* Container;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTabButton* Prefab;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> Names;
	
	virtual void NativeConstruct();

	void OnTabClicked(class UTabButton* button);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabSelected, const FString&, Tab);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTabSelected OnTabSelected;

protected:
	void UpdateButtons();

	class UTabButton* Selected = nullptr;
	TArray<class UTabButton*> Buttons;
};
