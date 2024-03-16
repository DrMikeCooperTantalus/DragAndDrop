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
	}

	return result;
}

void UDDSlot::SetObject(URPGObject* obj)
{
	Object->SetObject(obj);
	if (ParentContainer)
		ParentContainer->Drop(this, obj);
}

bool UDDSlot::CanDrop(URPGObject* obj)
{
	return ParentContainer == nullptr || ParentContainer->CanDrop(this, obj);
}
