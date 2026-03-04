// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnLua.h"
#include "lua.h"
#include "lauxlib.h"
#include "EvtMgr.generated.h"

//参数对象的类型
enum class ObjectType
{
	TypeBool,
	TypeInt,
	TypeNumber,
	TypeString,
	TypeTCHAR,
	TypeStruct,
	TypeObject
};

union BaseObjectValue
{
	bool bValue;
	double dValue;
	int64 iValue;
	void* pValue;
	const char* charValue;
	const TCHAR* tcharValue;
} ;

class UNLUALESSION_API FBaseObject
{
public:
	ObjectType Type;
public:
	FBaseObject(bool v)
	{
		Type = ObjectType::TypeBool;
		Value.bValue = v;
	}
	FBaseObject(float v)
	{
		Type = ObjectType::TypeNumber;
		Value.dValue = v;
	}
	FBaseObject(double v)
	{
		Type = ObjectType::TypeNumber;
		Value.dValue = v;
	}
	FBaseObject(int32 v)
	{
		Type = ObjectType::TypeInt;
		Value.iValue = v;
	}
	FBaseObject(int64 v)
	{
		Type = ObjectType::TypeInt;
		Value.iValue = v;
	}
	FBaseObject(long v)
	{
		Type = ObjectType::TypeInt;
		Value.iValue = v;
	}
	FBaseObject(void* v)
	{
		Type = ObjectType::TypeObject;
		Value.pValue = v;
	}
	FBaseObject(const char* v)
	{
		Type = ObjectType::TypeString;
		Value.charValue = v;
	}
	FBaseObject(FString& v)
	{
		Type = ObjectType::TypeTCHAR;
		Value.tcharValue = *v;
	}

	virtual ~FBaseObject()
	{
	}
	
	int32 GetInt() const { return (int32)Value.iValue; }
	int64 GetI64() const { return Value.iValue; }
	float GetFloat() const {return (float)Value.dValue;}
	double GetNumber() const { return Value.dValue; }

	const char * GetString() const { return Value.charValue; }
	const TCHAR* GetTCHAR() const { return Value.tcharValue; }

	bool GetBool() const { return Value.bValue;}
	void* GetData() const { return Value.pValue; }

	virtual FString GetName() const { return ""; }
	virtual void SetName(FString& pName)
	{
	}
	virtual void SetName(const char* pName) 
	{ 
	}
protected:
	BaseObjectValue Value;
};

class UNLUALESSION_API FStructObject : FBaseObject
{
	public:
	FStructObject(void* v) : FBaseObject(v)
	{
		Value.pValue = v;
		Type = ObjectType::TypeStruct;
	}
	FString GetName() const override
	{
		return name;
	}
	void SetName(FString& pName) override
	{
		name = pName;
	}
	void SetName(const char* pName) override
	{
		name = UTF8_TO_TCHAR(pName);
	}
private:
	FString name;
};

typedef void (*FEvtMgrHandler)(const void* Source, const TArray<FBaseObject*> Values);

class UNLUALESSION_API EvtMgrItem
{
public:
	EvtMgrItem() 
		:ID(0),
		Source(nullptr),
		Handler(nullptr),
		LuaFuncName(nullptr),
		TableName(""),
		isCancel(false)
	{
	}

	void Release();
public:
	int64 ID;
	void* Source;
	FEvtMgrHandler Handler;
	const char* LuaFuncName;
	FString TableName;
	bool isCancel;
};

/**
 * 
 */
UCLASS()
class UNLUALESSION_API UEvtMgr : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void Init();
	
	template<typename... Types>
	static void PushParams(TArray<FBaseObject*>& Param);

	template<typename T1, typename... Types>
	static void PushParams(TArray<FBaseObject*>& Param, T1&& V1, Types&&... args);

	template <typename... T>
	static void Dispatch(FString msg, T&&... args);
	static int LuaDispatch(lua_State* L);

	static void Execute(FString& msg, TArray<EvtMgrItem*>* items);
	static void ExecuteLua(EvtMgrItem* items);
	
	static int64 Listen(FString msg, void* S, FEvtMgrHandler Handler);
	static int LuaListen(lua_State* L);
	
	static void Push(TArray<FBaseObject*>& Param, bool V);
	
	static void Push(TArray<FBaseObject*>& Param, int8 V);
	static void Push(TArray<FBaseObject*>& Param, int16 V);
	static void Push(TArray<FBaseObject*>& Param, int32 V);
	static void Push(TArray<FBaseObject*>& Param, int64 V);
	static void Push(TArray<FBaseObject*>& Param, long V);
	static void Push(TArray<FBaseObject*>& Param, float V);
	static void Push(TArray<FBaseObject*>& Param, double V);

	static void Push(TArray<FBaseObject*>& Param, char* V);
	static void Push(TArray<FBaseObject*>& Param, const char* V);
	static void Push(TArray<FBaseObject*>& Param, FString&& V);
	static void Push(TArray<FBaseObject*>& Param, FString& V);
	static void Push(TArray<FBaseObject*>& Param, UObject* V);

	template <typename T>
	static void Push(TArray<FBaseObject*>& Param, T&& V);

	template <typename T>
	static FBaseObject* RequestObject(T&& V);

	template <typename T>
	static FBaseObject* RequestObject(T&& V, const char* pName);

	static void ReleaseObject(FBaseObject* element);

	static TArray<EvtMgrItem*>& FindEvtItems(FString& message);

public:
	static TMap<FString, TArray<EvtMgrItem*>> handlers;
	static int64 ItemIndex;

	static TArray<FBaseObject*> Datas;
};

template <typename... T>
void UEvtMgr::Dispatch(FString msg, T&&... args)
{
	PushParams(Datas, Forward<T>(args)...);

	TArray<EvtMgrItem*>* items = handlers.Find(msg);
	Execute(msg, items);
}

template <typename T>
FBaseObject* UEvtMgr::RequestObject(T&& V, const char* pName)
{
	FBaseObject* element = (FBaseObject*)new FStructObject(V);
	element->SetName(pName);
	return element;
}

template<typename T>
FBaseObject* UEvtMgr::RequestObject(T&& V)
{
	FBaseObject* element = element = (FBaseObject*)new FBaseObject(V);
	return element;
}


template <typename T> 
void UEvtMgr::Push(TArray<FBaseObject*>& Param, T&& V)
{
	bool IsUObject = TPointerIsConvertibleFromTo<typename TDecay<T>::Type, UObject>::Value;

	if (!IsUObject)
	{
		auto cName = UnLua::TType<typename TDecay<T>::Type>::GetName();
		FBaseObject* temp = RequestObject(&V, cName);
		Param.Emplace(temp);
	}
	else
	{
		Push(Param, (UObject*)&V);
	}
}

template<typename T1, typename... Types>
void  UEvtMgr::PushParams(TArray<FBaseObject*>& Param, T1&& V1, Types&&... args)
{
	Push(Param, Forward<T1>(V1));
	PushParams(Param, Forward<Types>(args)...);
}

template<typename... Types>
void UEvtMgr::PushParams(TArray<FBaseObject*>& Param)
{

}