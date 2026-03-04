// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LuaDelegateHandler.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeLuaDelegateHandler() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UNLUA_API UClass* Z_Construct_UClass_ULuaDelegateHandler();
UNLUA_API UClass* Z_Construct_UClass_ULuaDelegateHandler_NoRegister();
UPackage* Z_Construct_UPackage__Script_UnLua();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ULuaDelegateHandler Function Dummy ***************************************
struct Z_Construct_UFunction_ULuaDelegateHandler_Dummy_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LuaDelegateHandler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Dummy constinit property declarations *********************************
// ********** End Function Dummy constinit property declarations ***********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULuaDelegateHandler_Dummy_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ULuaDelegateHandler, nullptr, "Dummy", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULuaDelegateHandler_Dummy_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULuaDelegateHandler_Dummy_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ULuaDelegateHandler_Dummy()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULuaDelegateHandler_Dummy_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULuaDelegateHandler::execDummy)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Dummy();
	P_NATIVE_END;
}
// ********** End Class ULuaDelegateHandler Function Dummy *****************************************

// ********** Begin Class ULuaDelegateHandler ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ULuaDelegateHandler;
UClass* ULuaDelegateHandler::GetPrivateStaticClass()
{
	using TClass = ULuaDelegateHandler;
	if (!Z_Registration_Info_UClass_ULuaDelegateHandler.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("LuaDelegateHandler"),
			Z_Registration_Info_UClass_ULuaDelegateHandler.InnerSingleton,
			StaticRegisterNativesULuaDelegateHandler,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_ULuaDelegateHandler.InnerSingleton;
}
UClass* Z_Construct_UClass_ULuaDelegateHandler_NoRegister()
{
	return ULuaDelegateHandler::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ULuaDelegateHandler_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "LuaDelegateHandler.h" },
		{ "ModuleRelativePath", "Public/LuaDelegateHandler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ULuaDelegateHandler constinit property declarations **********************
// ********** End Class ULuaDelegateHandler constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Dummy"), .Pointer = &ULuaDelegateHandler::execDummy },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ULuaDelegateHandler_Dummy, "Dummy" }, // 857428356
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULuaDelegateHandler>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ULuaDelegateHandler_Statics
UObject* (*const Z_Construct_UClass_ULuaDelegateHandler_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_UnLua,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULuaDelegateHandler_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULuaDelegateHandler_Statics::ClassParams = {
	&ULuaDelegateHandler::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULuaDelegateHandler_Statics::Class_MetaDataParams), Z_Construct_UClass_ULuaDelegateHandler_Statics::Class_MetaDataParams)
};
void ULuaDelegateHandler::StaticRegisterNativesULuaDelegateHandler()
{
	UClass* Class = ULuaDelegateHandler::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_ULuaDelegateHandler_Statics::Funcs));
}
UClass* Z_Construct_UClass_ULuaDelegateHandler()
{
	if (!Z_Registration_Info_UClass_ULuaDelegateHandler.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULuaDelegateHandler.OuterSingleton, Z_Construct_UClass_ULuaDelegateHandler_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULuaDelegateHandler.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ULuaDelegateHandler);
ULuaDelegateHandler::~ULuaDelegateHandler() {}
// ********** End Class ULuaDelegateHandler ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_UEProject_UnLuaTPS_Plugins_UnLua_Source_UnLua_Public_LuaDelegateHandler_h__Script_UnLua_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULuaDelegateHandler, ULuaDelegateHandler::StaticClass, TEXT("ULuaDelegateHandler"), &Z_Registration_Info_UClass_ULuaDelegateHandler, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULuaDelegateHandler), 1825410421U) },
	};
}; // Z_CompiledInDeferFile_FID_UEProject_UnLuaTPS_Plugins_UnLua_Source_UnLua_Public_LuaDelegateHandler_h__Script_UnLua_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEProject_UnLuaTPS_Plugins_UnLua_Source_UnLua_Public_LuaDelegateHandler_h__Script_UnLua_4126216135{
	TEXT("/Script/UnLua"),
	Z_CompiledInDeferFile_FID_UEProject_UnLuaTPS_Plugins_UnLua_Source_UnLua_Public_LuaDelegateHandler_h__Script_UnLua_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UEProject_UnLuaTPS_Plugins_UnLua_Source_UnLua_Public_LuaDelegateHandler_h__Script_UnLua_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
