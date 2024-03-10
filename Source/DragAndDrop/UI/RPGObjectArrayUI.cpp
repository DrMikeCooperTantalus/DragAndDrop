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

void URPGObjectArrayUI::CreateSlots()
{
	// create a copy of the object and set for each element
	for (int i=0; i<Objects->Num(); i++)
	{
		UDDSlot* slot = DuplicateObject<UDDSlot>(Prefab, Container);
		Container->AddChild(slot);
		slot->Object->SetObject((*Objects)[i]);
	}

	// hide the prefab
	Prefab->SetVisibility(ESlateVisibility::Collapsed);
}
