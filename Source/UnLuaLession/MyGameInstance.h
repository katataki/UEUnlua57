// @COMPANY www.ngcod.com
// @AUTHOR ÃÏø’”Œµ¥µƒ”„
// QQ:708888157

#pragma once

#include "CoreMinimal.h"

#include "EvtMgr.h"
#include "Engine/GameInstance.h"
#include "UnLua.h"
#include "lua.h"
#include "MyGameInstance.generated.h"

#define CHECK_X() UnLua::FLuaRetValues Values = UnLua::CallTableFunc(L, "GameMgr", "ShowGameInfo")
#define CHECK_INIT() UnLua::CallTableFunc(L, "GameMgr", "Init")
/**
 * 
 */
UCLASS()
class UNLUALESSION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	static void HandEvent(const void* S, TArray<FBaseObject*> Params);
	
	virtual void StartGameInstance() override;
	UFUNCTION(BlueprintCallable)
		void InitEngine();

	UFUNCTION(BlueprintCallable)
		void NotifyNextLevel();
#if WITH_EDITOR
	/* Called to actually start the game when doing Play/Simulate In Editor */
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override;
#endif

	UFUNCTION()
		void OnTimerNextLevel();
private:
	FTimerHandle NextLevelTimer;
public:
	static int AddMul(lua_State* L);
};
