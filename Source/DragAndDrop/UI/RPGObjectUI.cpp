// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/RPGObjectUI.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DragAndDrop/RPGObject.h"

void URPGObjectUI::SetObject(URPGObject* obj)
{
	if (obj)
	{
		Name->SetText(FText::FromString(obj->GetName()));
		Icon->SetBrushFromTexture(obj->Icon);
	}
	SetVisibility(obj == nullptr ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	Obj = obj;
}
