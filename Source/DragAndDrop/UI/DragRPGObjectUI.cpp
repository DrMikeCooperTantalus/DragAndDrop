// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/DragRPGObjectUI.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "DDSlot.h"
#include "Components/PanelWidget.h"

void UDragRPGObjectUI::NativeConstruct()
{
	Super::NativeConstruct();
	ParentContainer = GetParent();
}

FReply UDragRPGObjectUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return ReplyResult.NativeReply;
}

void UDragRPGObjectUI::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                            UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* DragWidget = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	
	DragWidget->DefaultDragVisual = this;

	DragWidget->Pivot = EDragPivot::MouseDown;
	DragWidget->Payload = ParentSlot;

	if (!ParentSlot->ParentContainer->IsReadOnly())
	{
		DragWidget->DefaultDragVisual->SetVisibility(ESlateVisibility::HitTestInvisible);
		RemoveFromParent();
	}
	
	OutOperation = DragWidget;
}

void UDragRPGObjectUI::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	EndDrag();
	
	SetVisibility(ESlateVisibility::Visible);
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

void UDragRPGObjectUI::EndDrag()
{
	if (ParentContainer)
		ParentContainer->AddChild(this);
	RestoreMouse(GetWorld());
}

void UDragRPGObjectUI::RestoreMouse(UWorld* world)
{
	APlayerController* controller = GEngine->GetFirstLocalPlayerController(world);
	if (controller)
	{
		controller->SetShowMouseCursor(true);
		controller->CurrentMouseCursor = EMouseCursor::Default;
	}
}
