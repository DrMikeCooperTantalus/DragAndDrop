// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/RPGEquipScreen.h"

#include "RPGObjectUI.h"
#include "DragAndDrop/DragAndDropCharacter.h"
#include "DragAndDrop/RPGObject.h"
#include "RPGEquipScreen.h"

bool URPGEquipScreen::CanDrop(UDDSlot* slot, URPGObject* obj)
{
	return obj == nullptr
		|| (slot == HelmetSlot && obj->ItemType == ERPGItemType::Helmet)
		|| (slot == WeaponSlot && obj->ItemType == ERPGItemType::Weapon)
		|| (slot == ScrollSlot && obj->ItemType == ERPGItemType::Scroll);
}

void URPGEquipScreen::Drop(UDDSlot* slot, URPGObject* obj)
{
	if (Character)
	{
		if (slot == HelmetSlot) Character->EquippedHelmet = obj;
		if (slot == WeaponSlot) Character->EquippedWeapon = obj;
		if (slot == ScrollSlot) Character->EquippedScroll = obj;
	}
}

void URPGEquipScreen::OnDoubleClicked(int index)
{
	OnDoubleClick.Broadcast(index);
}

void URPGEquipScreen::NativeConstruct()
{
	Super::NativeConstruct();
	HelmetSlot->ParentContainer = this;
	WeaponSlot->ParentContainer = this;
	ScrollSlot->ParentContainer = this;

	HelmetSlot->Index = 0;
	WeaponSlot->Index = 1;
	ScrollSlot->Index = 2;
}

void URPGEquipScreen::SetCharacter(ADragAndDropCharacter* ch)
{
	Character = ch;
	HelmetSlot->Object->SetObject(ch->EquippedHelmet);
	WeaponSlot->Object->SetObject(ch->EquippedWeapon);
	ScrollSlot->Object->SetObject(ch->EquippedScroll);
}

class URPGObject* URPGEquipScreen::GetObject(int index)
{
	switch (index)
	{
	case 0: return HelmetSlot->Object->GetObj();
	case 1: return WeaponSlot->Object->GetObj();
	case 2: return ScrollSlot->Object->GetObj();
	}
	return nullptr;
}

void URPGEquipScreen::SetObject(int index, class URPGObject* object)
{
	switch (index)
	{
	case 0:
		Character->EquippedHelmet = object;
		HelmetSlot->Object->SetObject(object);
		break;
	case 1:
		Character->EquippedWeapon = object;
		WeaponSlot->Object->SetObject(object);
		break;
	case 2:
		Character->EquippedScroll = object;
		ScrollSlot->Object->SetObject(object);
		break;
	}
}