// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLuaUtils.h"

int UMyLuaUtils::GetInt()
{
	return 100;
}

void UMyLuaUtils::AddTimeLine(UObject* Outer, FString CurvePath, ETimelineLengthMode mode, FOnTimelineFloat CallBack)
{
	UActorComponent* Component = Cast<AActor>(Outer)->AddComponentByClass(UTimelineComponent::StaticClass(), true, FTransform(), true);
	UTimelineComponent* TimelineComponent = Cast<UTimelineComponent>(Component);

	UObject* Curve = LoadObject<UObject>(Outer, *CurvePath);
	
	TimelineComponent->AddInterpFloat(Cast<UCurveFloat>(Curve), CallBack);
	TimelineComponent->SetTimelineLengthMode(mode);
	TimelineComponent->PlayFromStart();

	
	/*FTimeline timeLine;
	timeLine.SetTimelineLengthMode(mode);

	timeLine.AddInterpFloat(Cast<UCurveFloat>(Curve), CallBack);
	timeLine.PlayFromStart();*/
}

