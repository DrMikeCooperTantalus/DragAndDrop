// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/GameHUD.h"
#include "DragAndDrop/UI/RPGEquipScreen.h"
#include "DragAndDrop/UI/RPGObjectArrayUI.h"
#include "DragAndDrop/DragAndDropCharacter.h"

void UGameHUD::SetCharacter(ADragAndDropCharacter* ch)
{
	BackPack->SetObjects(&ch->BackPack);
	Belt->SetObjects(&ch->Belt);
	EquipScreen->SetCharacter(ch);
}
