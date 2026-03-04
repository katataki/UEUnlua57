// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/TimelineComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyLuaUtils.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FTimeLineCallBack, float, Delta);

/**
 * 
 */
UCLASS()
class UNLUALESSION_API UMyLuaUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		static int GetInt();
	UFUNCTION(BlueprintCallable)
		void AddTimeLine(UObject* Outer, FString CurvePath, ETimelineLengthMode mode, FOnTimelineFloat CallBack);
};
