// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/DDSlot.h"

#include <ObjectArray.h>

#include "DragRPGObjectUI.h"
#include "RPGObjectArrayUI.h"
#include "RPGObjectUI.h"
#include "Blueprint/DragDropOperation.h"

void UDDSlot::NativeConstruct()
{
	Super::NativeConstruct();
	Object->ParentSlot = this;
}

void UDDSlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	// look at the object hovered over us and see if we can accept it as a valid drop
	UDDSlot* sourceSlot = Cast<UDDSlot>(InOperation->Payload.Get());
	if (sourceSlot)
	{
		URPGObject* objMine = Object->GetObj();
		URPGObject* objTheirs = sourceSlot->Object->GetObj();
		// find the appropriate animation - need to check the swap both ways
		LastAnimation = (CanDrop(objTheirs) && sourceSlot->CanDrop(objMine)) ? OpenToDrop : CloseVsDrop;
		if (LastAnimation)
			PlayAnimation(LastAnimation);
	}
}

void UDDSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	if (LastAnimation)
	{
		PlayAnimation(LastAnimation,1,1,EUMGSequencePlayMode::Reverse);
		LastAnimation = nullptr;
	}
}


bool UDDSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                           UDragDropOperation* InOperation)
{
	bool result  = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDDSlot* sourceSlot = Cast<UDDSlot>(InOperation->Payload.Get());
	if (sourceSlot)
	{
		// swap our objects around
		URPGObject* objMine = Object->GetObj();
		URPGObject* objTheirs = sourceSlot->Object->GetObj();

		if (CanDrop(objTheirs) && sourceSlot->CanDrop(objMine))
		{
			sourceSlot->SetObject(objMine);
			SetObject(objTheirs);
			result = true;

			UDragRPGObjectUI* dragObjectUI = Cast<UDragRPGObjectUI>(sourceSlot->Object);
			if (dragObjectUI)
				dragObjectUI->EndDrag();
		}

		if (LastAnimation)
		{
			PlayAnimation(LastAnimation,1,1,EUMGSequencePlayMode::Reverse);
			LastAnimation = nullptr;
		}
	}

	return result;
}

void UDDSlot::SetObject(URPGObject* obj)
{
	if (!ParentContainer->IsReadOnly())
		Object->SetObject(obj);
	if (ParentContainer)
		ParentContainer->Drop(this, obj);
}

bool UDDSlot::CanDrop(URPGObject* obj)
{
	return ParentContainer == nullptr || ParentContainer->CanDrop(this, obj);
}
