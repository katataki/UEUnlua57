// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreUI.h"

void UCoreUI::TestCallable()
{
	TestNativeEvent();
}

void UCoreUI::TestNativeEvent_Implementation()
{
	TestImplementable();
}

void UCoreUI::AddDelegate(FMyDelegate pDelegate)
{
	Delegate = MoveTemp(pDelegate);
}

void UCoreUI::CallDelegate()
{
	if (Delegate.IsBound())
	{
		Delegate.Execute();
	}
}

void UCoreUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	TestCallable();
	TestImplementable();
}
