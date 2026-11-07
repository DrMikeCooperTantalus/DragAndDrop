// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDrop/UI/GameHUD.h"
#include "DragAndDrop/UI/RPGEquipScreen.h"
#include "DragAndDrop/UI/RPGObjectArrayUI.h"
#include "DragAndDrop/DragAndDropCharacter.h"
#include "GameHUD.h"

void UGameHUD::NativeConstruct()
{
   Super::NativeConstruct();

   BackPack->OnDoubleClick.AddDynamic(this, &UGameHUD::OnBackPackDoubleClick);
   Belt->OnDoubleClick.AddDynamic(this, &UGameHUD::OnBeltDoubleClick);
   EquipScreen->OnDoubleClick.AddDynamic(this, &UGameHUD::OnEquipmentDoubleClick);
}

void UGameHUD::SetCharacter(ADragAndDropCharacter* ch)
{
   Character = ch;

   BackPack->SetObjects(&ch->BackPack);
   Belt->SetObjects(&ch->Belt);
   EquipScreen->SetCharacter(ch);
}

void UGameHUD::OnBackPackDoubleClick(int index)
{
   //depends on the type of item...
   if (Character.IsValid())
   {
      URPGObject* obj = Character->BackPack[index];
      if (obj)
      {
         switch (obj->ItemType)
         {
         case Potion:
         {
            for (int swapIndex = 0; swapIndex < Character->Belt.Num(); swapIndex++)
            {
               if (Character->Belt[swapIndex] == nullptr)
               {
                  Character->Belt[swapIndex] = Character->BackPack[index];
                  Character->BackPack[index] = nullptr;
                  BackPack->Refresh();
                  Belt->Refresh();
                  return;
               }
            }
         }
         break;
         case Helmet:
         {
            Character->BackPack[index] = Character->EquippedHelmet;
            EquipScreen->SetObject(0, obj);
            BackPack->Refresh();
         }
         break;
         case Weapon:
         {
            Character->BackPack[index] = Character->EquippedWeapon;
            EquipScreen->SetObject(1, obj);
            BackPack->Refresh();
         }
         break;
         case Scroll:
         {
            Character->BackPack[index] = Character->EquippedScroll;
            EquipScreen->SetObject(2, obj);
            BackPack->Refresh();
         }
         break;
         }
      }
   }
}

void UGameHUD::OnBeltDoubleClick(int index)
{
   // move clicked item from belt into a slot in the backpack
   if (Character.IsValid())
   {
      for (int swapIndex = 0; swapIndex < Character->BackPack.Num(); swapIndex++)
      {
         if (Character->BackPack[swapIndex] == nullptr)
         {
            Character->BackPack[swapIndex] = Character->Belt[index];
            Character->Belt[index] = nullptr;
            BackPack->Refresh();
            Belt->Refresh();
            return;
         }
      }
   }
}

void UGameHUD::OnEquipmentDoubleClick(int index)
{
   // move clicked item from belt into a slot in the backpack
   if (Character.IsValid())
   {
      for (int swapIndex = 0; swapIndex < Character->BackPack.Num(); swapIndex++)
      {
         if (Character->BackPack[swapIndex] == nullptr)
         {
            Character->BackPack[swapIndex] = EquipScreen->GetObject(index);
            EquipScreen->SetObject(index, nullptr);
            BackPack->Refresh();
            return;
         }
      }
   }
}
