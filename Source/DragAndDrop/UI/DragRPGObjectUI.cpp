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
	DragWidget->DefaultDragVisual->SetVisibility(ESlateVisibility::HitTestInvisible);
	DragWidget->Pivot = EDragPivot::MouseDown;
	DragWidget->Payload = ParentSlot;
	
	Icon->SetColorAndOpacity(FColor(255,0,0));

	RemoveFromParent();
	
	OutOperation = DragWidget;
}

void UDragRPGObjectUI::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	Icon->SetColorAndOpacity(FColor(0, 255,0));
}

void UDragRPGObjectUI::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                         UDragDropOperation* InOperation)
{
	Icon->SetColorAndOpacity(FColor(0, 0, 255));
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void UDragRPGObjectUI::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	EndDrag();
	
	SetVisibility(ESlateVisibility::Visible);
	Icon->SetColorAndOpacity(FColor(255, 255,255));
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
