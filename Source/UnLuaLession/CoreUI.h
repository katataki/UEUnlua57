// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "UnLuaLession.h"
#include "CoreUI.generated.h"

DECLARE_DYNAMIC_DELEGATE(FMyDelegate);
/**
 * 
 */
UCLASS()
class UNLUALESSION_API UCoreUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "User Interface")
		void TestImplementable();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")
		void TestCallable();
	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, Category = "User Interface")
		void TestNativeEvent();
	void TestNativeEvent_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")
		void AddDelegate(FMyDelegate Delegate);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "User Interface")
		void CallDelegate();

	virtual void NativeOnInitialized() override;
private:
	FMyDelegate Delegate;
};
