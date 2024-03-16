// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DRAGANDDROP_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class URPGObjectArrayUI* Belt;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class URPGObjectArrayUI* BackPack;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class URPGEquipScreen* EquipScreen;
	
	UFUNCTION(BlueprintCallable)
	void SetCharacter(class ADragAndDropCharacter* ch);
};
