// @COMPANY www.ngcod.com
// @AUTHOR ÃÏø’”Œµ¥µƒ”„
// QQ:708888157


#include "BasePlayerController.h"

#include "Net/UnrealNetwork.h"

void ABasePlayerController::Reborn_Implementation()
{
	K2_Reborn();
}

void ABasePlayerController::HurtServer_Implementation(const FString& KilledName, const FString& InstigatorName)
{
	HurtMulticast(KilledName, InstigatorName);
}

void ABasePlayerController::HurtMulticast_Implementation(const FString& KilledName, const FString& InstigatorName)
{
	K2_Hurt(KilledName, InstigatorName);
}

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	IDX = 0;
}

void ABasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasePlayerController, IDX);
}
