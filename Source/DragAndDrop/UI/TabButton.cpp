// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/TabButton.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Tabs.h"

void UTabButton::NativeConstruct()
{
   Button->OnClicked.AddDynamic(this, &UTabButton::OnClicked);
}

void UTabButton::Init(FString& name, class UTabs* parent)
{
   ParentTabs = parent;
   TabName = name;
   Name->SetText(FText::FromString(name));
}

void UTabButton::OnClicked()
{
   if (ParentTabs)
      ParentTabs->OnTabClicked(this);
}

void UTabButton::ShowSelect(bool On)
{
   if (On != Selected)
   {
      Selected = On;
      if (On)
         PlayAnimationForward(Select);
      else
         PlayAnimationReverse(Select);
   }
}


