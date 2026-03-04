// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "EvtMgr.h"
#include "UnLua.h"
#include "lua.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UnLuaDelegates.h"

void UMyGameInstance::HandEvent(const void* S, TArray<FBaseObject*> Params)
{
	UE_LOG(LogTemp, Warning, TEXT("AAA %d %s"), Params[0]->GetInt(), UTF8_TO_TCHAR(Params[3]->GetString()));
}

void UMyGameInstance::StartGameInstance()
{
    Super::StartGameInstance();
	InitEngine();
}

void UMyGameInstance::InitEngine()
{
	lua_State* L = UnLua::GetState();
	lua_register(L, "AddMul", AddMul);

	const FString RelName = TEXT("GameMgr.lua");

	FString FilePath = FPaths::ProjectContentDir() / RelName;
	FString LuaCode;
	if (FFileHelper::LoadFileToString(LuaCode, *FilePath))
	{
		// 通过 FLuaEnv 执行
		UnLua::FLuaEnv* Env = UnLua::FLuaEnv::FindEnv(L);
		if (Env)
		{
			bool result = Env->DoString(TCHAR_TO_ANSI(*LuaCode));
			if (!result)
			{
				return;
			}
		}
	}
	
	//bool result = UnLua::RunFile(L, RelName);
	//if (!result)
	//{
	//	return;
	//}

	//UnLua::FLuaRetValues Values = UnLua::CallTableFunc(L, "GameMgr", "ShowGameInfo");
	CHECK_X();
	if (Values.Num() < 1)
	{
		return;
	}
	const UnLua::FLuaValue& P1 = Values[0];
	FString p1 = P1.Value<FString>();
	if (p1 != "www.ngcod.com")
	{
		return;
	}
	CHECK_INIT();
	//UnLua::CallTableFunc(L, "GameMgr", "Init");

	const FString RelNameLua = TEXT("UnLua.lua");

	// 读取 Lua 文件内容为字符串，然后执行
	FString FilePath2 = FPaths::ProjectContentDir() / RelNameLua;
	FString LuaCode2;
	if (FFileHelper::LoadFileToString(LuaCode2, *FilePath2))
	{
		// 通过 FLuaEnv 执行
		UnLua::FLuaEnv* Env = UnLua::FLuaEnv::FindEnv(L);
		if (Env)
		{
			Env->DoString(TCHAR_TO_ANSI(*LuaCode2));
		}
	}

	//UnLua::RunFile(L, RelNameLua);
	
	UEvtMgr::Init();
	UEvtMgr::Listen("AAA", this, &UMyGameInstance::HandEvent);
}

void UMyGameInstance::NotifyNextLevel()
{
	if (NextLevelTimer.IsValid())
	{
		return;
	}
	UWorld* TheWorld = this->GetWorld();
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, "OnTimerNextLevel");
	if (TimerDelegate.IsBound())
	{
		TheWorld->GetTimerManager().SetTimer(NextLevelTimer, TimerDelegate, 20, true);
	}
}
#if WITH_EDITOR
FGameInstancePIEResult UMyGameInstance::StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params)
{
	FGameInstancePIEResult InitResult = FGameInstancePIEResult::Failure(FText());

	InitEngine();

	FGameInstancePIEResult StartResult = Super::StartPlayInEditorGameInstance(LocalPlayer, Params);

	return StartResult;
}
void UMyGameInstance::OnTimerNextLevel()
{
	UWorld* TheWorld = this->GetWorld();
	TheWorld->GetTimerManager().ClearTimer(NextLevelTimer);

	lua_State* L = UnLua::GetState();
	UnLua::CallTableFunc(L, "GameMgr", "GotoNextLevel");
}

int UMyGameInstance::AddMul(lua_State* L)
{
	int num = lua_gettop(L) + 1;
	int result = 0;
	for (int i = 1; i < num; i++)
	{
		if (lua_isnumber(L, i))
		{
			result += luaL_checknumber(L, i);
		}
		else if (lua_istable(L, i))
		{
			lua_pushvalue(L, i);
			lua_pushstring(L, "Count");
			lua_gettable(L, -2);
			result += luaL_checknumber(L, -1);
			lua_pop(L, 2);
		}
	}
	lua_pop(L, -1);
	lua_newtable(L);
	lua_pushstring(L, "Result");
	lua_pushnumber(L, result);
	lua_settable(L, -3);

	lua_pushstring(L, "Num");
	lua_pushnumber(L, num);
	lua_settable(L, -3);

	return 1;
}
#endif
