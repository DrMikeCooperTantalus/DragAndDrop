// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/RPGObjectUI.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DDSlot.h"
#include "DragAndDrop/RPGObject.h"

void URPGObjectUI::SetObject(URPGObject* obj)
{
	if (obj)
	{
		Name->SetText(FText::FromString(obj->GetName()));
		Icon->SetBrushFromTexture(obj->Icon);
	}
	// make the object invisible if it's null eg empty inventory slot
	SetVisibility(obj == nullptr ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	// store a live pointer
	Obj = obj;
}

FReply URPGObjectUI::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (ParentSlot && ParentSlot->ParentContainer)
		ParentSlot->ParentContainer->OnDoubleClicked(ParentSlot->Index);
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}