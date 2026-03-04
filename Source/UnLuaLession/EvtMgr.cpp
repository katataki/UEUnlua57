// Fill out your copyright notice in the Description page of Project Settings.


#include "EvtMgr.h"

void EvtMgrItem::Release()
{
	delete this;
}

TMap<FString, TArray<EvtMgrItem*>> UEvtMgr::handlers;

int64 UEvtMgr::ItemIndex = 1;
TArray<FBaseObject*> UEvtMgr::Datas;


int64 UEvtMgr::Listen(FString msg, void* S, FEvtMgrHandler Handler)
{
	EvtMgrItem* Item = new EvtMgrItem();
	Item->ID = ItemIndex;
	Item->Source = S;
	Item->Handler = Handler;

	TArray<EvtMgrItem*>& elements = FindEvtItems(msg);
	elements.Emplace(Item);
	ItemIndex++;
	return Item->ID;
}

int UEvtMgr::LuaListen(lua_State* L)
{
	int Num = lua_gettop(L);
	if (Num != 3)
	{
		lua_pushinteger(L, 0);
		return 1;
	}
	const char* charMsg = luaL_checkstring(L, 2);
	const char* FunctionName = luaL_checkstring(L, 3);

	FString message = UTF8_TO_TCHAR(charMsg);
	FString TableName = FString::Printf(TEXT("%s%d"), *message, ItemIndex);

	const char* cTableName = TCHAR_TO_UTF8(*TableName);

	EvtMgrItem* Item = new EvtMgrItem();
	Item->LuaFuncName = FunctionName;
	Item->TableName = TableName;
	Item->ID = ItemIndex;
	
	TArray<EvtMgrItem*>& elements = FindEvtItems(message);
	elements.Emplace(Item);

	lua_pop(L, 2);

	lua_setglobal(L, cTableName);

	lua_pushinteger(L, Item->ID);
	ItemIndex++;
	return 1;
}

void UEvtMgr::Init()
{
	lua_State* L = UnLua::GetState();
	lua_newtable(L);
	lua_pushstring(L, "Dispatch");
	lua_pushcfunction(L, LuaDispatch);
	lua_settable(L, -3);

	lua_pushstring(L, "Listen");
	lua_pushcfunction(L, LuaListen);
	lua_settable(L, -3);

	lua_setglobal(L, "EvtMgr");
}

int UEvtMgr::LuaDispatch(lua_State* L)
{
	int ArgNum = lua_gettop(L);
	int count = ArgNum + 1;

	const char* cMessage = luaL_checkstring(L, 1);
	FString message = UTF8_TO_TCHAR(cMessage);

	TArray<EvtMgrItem*>* items = handlers.Find(message);
	if (nullptr == items)
	{
		return 0;
	}

	for (int i = 2; i < count; i++)
	{
		int type = lua_type(L, i);
		switch (type)
		{
		case LUA_TBOOLEAN:
			{
				int V = lua_toboolean(L, i);
				FBaseObject* temp = RequestObject(V == 1 ? true : false);
				Datas.Emplace(temp);
				break;
			}
		case LUA_TNUMBER:
			{
				double V = luaL_checknumber(L, i);
				FBaseObject* temp = RequestObject(V);
				Datas.Emplace(temp);
				break;
			}
		case LUA_TSTRING:
			{
				const char* V = luaL_checkstring(L, i);
				FBaseObject* temp = RequestObject(V);
				Datas.Emplace(temp);
				break;
			}
		case LUA_TTABLE:
			{
				UObject* userData = UnLua::GetUObject(L, i);
				FBaseObject* temp = RequestObject(userData);
				Datas.Emplace(temp);
				break;
			}
		case LUA_TUSERDATA:
			{
				lua_pushvalue(L, i);
				lua_getmetatable(L, -1);
				if (!lua_istable(L, -1))
				{
					break;
				}
				lua_pushstring(L, "__name");
				lua_gettable(L, -2);
				const char* cName = luaL_checkstring(L, -1);

				lua_pop(L, 3);
			
				void* userData = UnLua::GetPointer(L, i);
				FBaseObject* temp = RequestObject(userData, cName);
				Datas.Emplace(temp);
				break;
			}
		default:
			{
				int64 V = luaL_checkinteger(L, i);
				FBaseObject* temp = RequestObject(V);
				Datas.Emplace(temp);
				break;
			}
		}
	}
	lua_pop(L, -1);
	Execute(message, items);
	return 0;
}

void UEvtMgr::ExecuteLua(EvtMgrItem* Item)
{
	lua_State* L = UnLua::GetState();
	if (nullptr != L)
	{
		lua_pushcfunction(L, UnLua::ReportLuaCallError);

		lua_getglobal(L, TCHAR_TO_UTF8(*Item->TableName));
		if (!lua_istable(L, -1))
		{
			lua_pop(L, 2);
			return;
		}
		const char* FuncName = Item->LuaFuncName;
		lua_pushstring(L, FuncName);
		lua_gettable(L, -2);

		if (lua_isfunction(L, -1))
		{
			//第一个参数为self
			lua_pushvalue(L, -2);

			int32 MessageHandlerIdx = lua_gettop(L) - 1;
			check(MessageHandlerIdx > 0);
			int32 NumArgs = Datas.Num();
			for (int i = 0; i < NumArgs; i++)
			{
				FBaseObject* tempObject = Datas[i];
				switch (tempObject->Type)
				{
				case ObjectType::TypeBool:
				{
					lua_pushboolean(L, tempObject->GetBool() ? 1 : 0);
					break;
				}
				case ObjectType::TypeInt:
				{
					lua_pushinteger(L, tempObject->GetI64());
					break;
				}
				case ObjectType::TypeNumber:
				{
					lua_pushnumber(L, tempObject->GetNumber());
					break;
				}
				case ObjectType::TypeString:
				{
					const char* ValueStr = tempObject->GetString();
					int size = strlen(ValueStr);
					lua_pushlstring(L, ValueStr, size);
					break;
				}
				case ObjectType::TypeTCHAR:
				{
					const TCHAR* ValueTCHAR = tempObject->GetTCHAR();
					const char* ValueStr = TCHAR_TO_UTF8(ValueTCHAR);
					int size = strlen(ValueStr);
					lua_pushlstring(L, ValueStr, size);
					break;
				}
				case ObjectType::TypeStruct:
				{
					void* Value = tempObject->GetData();
					const char* Name = TCHAR_TO_UTF8(*(tempObject->GetName()));
					UnLua::PushPointer(L, Value, Name);
					break;
				}
				case ObjectType::TypeObject:
				{
					UObject* Value = (UObject*)(tempObject->GetData());
					UnLua::PushUObject(L, Value);
					break;
				}
				default:
					break;
				}
			}
			int32 Code = lua_pcall(L, NumArgs + 1, LUA_MULTRET, MessageHandlerIdx);
			int32 TopIdx = lua_gettop(L);
			if (Code == LUA_OK)
			{
				lua_remove(L, MessageHandlerIdx);
			}
			lua_pop(L, TopIdx - MessageHandlerIdx + 1);
		}
		else
		{
			lua_pop(L, 2);
		}
	}
}

void UEvtMgr::Execute(FString& msg, TArray<EvtMgrItem*>* items)
{
	if (nullptr == items)
	{
		return;
	}

	TArray<EvtMgrItem*> cancelItems;
	for (auto& Item : *items)
	{
		if (Item->isCancel)
		{
			cancelItems.Emplace(Item);
			continue;
		}
		if (Item->Handler != nullptr && Item->Source != nullptr)
		{
			Item->Handler(Item->Source, Datas);
			if (Item->isCancel)
			{
				cancelItems.Emplace(Item);
			}
			continue;
		}				
		if (nullptr == Item->LuaFuncName || TEXT("") == Item->TableName)
		{
			continue;
		}
		ExecuteLua(Item);
		if (Item->isCancel)
		{
			cancelItems.Emplace(Item);
		}
	}

	for (auto& cancleItem : cancelItems)
	{
		items->Remove(cancleItem);
		cancleItem->Release();
	}
	
	for (auto& Element : Datas)
	{
		ReleaseObject(Element);
	}
	Datas.Empty();
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, bool V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, char* V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, const char* V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*> &Param, FString&& V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, FString& V)
{
	FBaseObject* temp = RequestObject(MoveTemp(V));
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, int8 V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, int16 V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, int32 V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, int64 V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, long V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, float V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, double V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::Push(TArray<FBaseObject*>& Param, UObject* V)
{
	FBaseObject* temp = RequestObject(V);
	Param.Emplace(temp);
}

void UEvtMgr::ReleaseObject(FBaseObject* element)
{
	if (nullptr == element)
	{
		return;
	}
	delete element;
}

TArray<EvtMgrItem*>& UEvtMgr::FindEvtItems(FString& message)
{
	TArray<EvtMgrItem*>* elements = nullptr;
	elements = handlers.Find(message);
	if (nullptr == elements)
	{
		TArray<EvtMgrItem*> items;
		handlers.Emplace(message, items);
		elements = handlers.Find(message);
	}
	return *elements;
}
