// @COMPANY www.ngcod.com
// @AUTHOR ÃÏø’”Œµ¥µƒ”„
// QQ:708888157

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNLUALESSION_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Reborn();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_Reborn();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void HurtServer(const FString& KilledName, const FString& InstigatorName);
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void HurtMulticast(const FString& KilledName, const FString& InstigatorName);

	UFUNCTION(BlueprintImplementableEvent)
	void K2_Hurt(const FString& KilledName, const FString& InstigatorName);
public:
	UPROPERTY(Replicated)
	int32 IDX;
};
