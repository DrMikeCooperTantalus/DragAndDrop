// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/Tabs.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TabButton.h"
#include "Components/PanelWidget.h"
#include "DragAndDrop/RPGObject.h"


void UTabs::NativeConstruct()
{
   for (auto Name : Names)
   {
      UTabButton* Button = DuplicateObject<UTabButton>(Prefab, Container);
      Container->AddChild(Button);
      Button->Init(Name, this);
      Buttons.Add(Button);
   }
   Prefab->SetVisibility(ESlateVisibility::Collapsed);

   if (Buttons.IsEmpty() == false)
      OnTabClicked(Buttons[0]);
}

void UTabs::OnTabClicked(class UTabButton* button)
{
   Selected = button;
   UpdateButtons();
   OnTabSelected.Broadcast(button->GetTabName());
}

void UTabs::UpdateButtons()
{
   for (auto Button : Buttons)
   {
      Button->ShowSelect(Button == Selected);
   }
}