// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/RPGEquipScreen.h"

#include "RPGObjectUI.h"
#include "DragAndDrop/DragAndDropCharacter.h"
#include "DragAndDrop/RPGObject.h"

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

void URPGEquipScreen::NativeConstruct()
{
	Super::NativeConstruct();
	HelmetSlot->ParentContainer = this;
	WeaponSlot->ParentContainer = this;
	ScrollSlot->ParentContainer = this;
}

void URPGEquipScreen::SetCharacter(ADragAndDropCharacter* ch)
{
	Character = ch;
	HelmetSlot->Object->SetObject(ch->EquippedHelmet);
	WeaponSlot->Object->SetObject(ch->EquippedWeapon);
	ScrollSlot->Object->SetObject(ch->EquippedScroll);
}
