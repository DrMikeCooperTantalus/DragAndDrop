// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/RPGObjectArrayUI.h"

#include "DragAndDrop/UI/RPGObjectUI.h"
#include "DragAndDrop/UI/DDSlot.h"
#include "Components/PanelWidget.h"

void URPGObjectArrayUI::SetObjects(TArray<URPGObject*>* objects)
{
	Objects = objects;
	CreateSlots();
}

bool URPGObjectArrayUI::CanDrop(UDDSlot* slot, URPGObject* obj)
{
	if (obj == nullptr)
		return true;

	uint8 type = static_cast<uint8>(obj->ItemType.GetValue());
	return (type & AllowedTypes) != 0;
}

void URPGObjectArrayUI::Drop(UDDSlot* slot, URPGObject* obj)
{
	if (Objects->IsValidIndex(slot->Index))
		(*Objects)[slot->Index] = obj;
}

void URPGObjectArrayUI::CreateSlots()
{
	// create a copy of the object and set for each element
	for (int i=0; i<Objects->Num(); i++)
	{
		UDDSlot* slot = DuplicateObject<UDDSlot>(Prefab, Container);
		Container->AddChild(slot);
		slot->Object->SetObject((*Objects)[i]);
		slot->Index = i;
		slot->ParentContainer = this;
	}

	// hide the prefab
	Prefab->SetVisibility(ESlateVisibility::Collapsed);
}
