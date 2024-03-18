// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DragAndDrop/UI/RPGObjectUI.h"
#include "DragRPGObjectUI.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API UDragRPGObjectUI : public URPGObjectUI
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	// this gets called when the mouse buttons go down, and are used to detect if a drag should start
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	// called when the user has started to drag this component
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	// called when the mouse is released while dragging, and nothing has returned a positive result for OnNativeDrop
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void EndDrag();
	static void RestoreMouse(UWorld* world);
	
protected:
	class UPanelWidget* ParentContainer;
};
