// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBaseActor.generated.h"

UCLASS()
class UNLUALESSION_API AMyBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
		int GetIndex();
	UFUNCTION(BlueprintImplementableEvent)
		void LuaImp();
	UFUNCTION(BlueprintNativeEvent)
		void LuaNative();
	void LuaNative_Implementation();
public:
	UPROPERTY(EditAnywhere)
	FString Name;
private:
	int index;

};
