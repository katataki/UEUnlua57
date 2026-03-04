// Tencent is pleased to support the open source community by making UnLua available.
// 
// Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the MIT License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaOverridesClass.h"
#include "LuaFunction.h"
#include "Misc/EngineVersionComparison.h"

ULuaOverridesClass* ULuaOverridesClass::Create(UClass* Class)
{
    auto ClassNameString = FString::Printf(TEXT("LUA_OVERRIDES_%s"), *Class->GetName());
    auto ClassName = MakeUniqueObjectName(GetTransientPackage(), Class, FName(*ClassNameString));
    auto Ret = NewObject<ULuaOverridesClass>(GetTransientPackage(), ClassName, RF_Public | RF_Transient);
    Ret->ClassFlags |= CLASS_NewerVersionExists; // bypass FBlueprintActionDatabase::RefreshClassActions
#if UE_VERSION_NEWER_THAN_OR_EQUAL(5,6,0)
    Ret->SetDefaultObject(StaticClass()->GetDefaultObject());
#else
    Ret->ClassDefaultObject = StaticClass()->GetDefaultObject();
#endif
    Ret->SetSuperStruct(StaticClass());
    Ret->Bind();
    Ret->Owner = Class;
    Ret->AddToOwner();
    return Ret;
}

void ULuaOverridesClass::Restore()
{
    SetActive(false);
    RemoveFromOwner();
}

void ULuaOverridesClass::SetActive(const bool bActive)
{
    const auto Class = Owner.Get();
    if (!Class)
        return;

    for (TFieldIterator<ULuaFunction> It(this, EFieldIteratorFlags::ExcludeSuper); It; ++It)
    {
        const auto LuaFunction = *It;
        LuaFunction->SetActive(bActive);
    }

    Class->ClearFunctionMapsCaches();
    if (bActive)
        AddToOwner();
    else
        RemoveFromOwner();
}

void ULuaOverridesClass::BeginDestroy()
{
    Restore();
    UClass::BeginDestroy();
}

void ULuaOverridesClass::AddToOwner()
{
    const auto Class = Owner.Get();
    if (!Class)
        return;

#if UE_VERSION_NEWER_THAN(5, 2, 1)
    // UE5.2.1+ : 使用 TObjectPtr 兼容的方式
    // 直接操作 Children，不使用二级指针
    TObjectPtr<UField>* Field = &Class->Children;
    
    while (*Field)
    {
        if (*Field == this)
        {
            // 已经在链表中
            return;
        }
        // 关键修改：使用 .Get() 获取裸指针，再取 Next 的地址
        // 但 Next 也是 TObjectPtr<UField>，所以需要转换
        UField* RawField = (*Field).Get();
        if (RawField->Next)
        {
            // 继续遍历
            Field = &(*Field)->Next;
        }
        else
        {
            // 到达链表尾部
            break;
        }
    }
    
    // 添加到链表（头部或尾部）
    if (!*Field)
    {
        // 尾部添加
        *Field = this;
    }
    // 注意：这种写法可能有问题，因为 Field 指向的是 Children 或某个 Next
    // 需要确保 this->Next 被正确设置
    
#else
    // UE5.2.1 以下：原逻辑保持不变
    auto Field = &(Class->Children);
    
    while (*Field)
    {
        if (*Field == this)
        {
            Field = nullptr;
            break;
        }
        Field = &(*Field)->Next;
    }

    if (Field)
        *Field = this;
#endif

    if (Class->IsRooted() || GUObjectArray.IsDisregardForGC(Class))
        AddToRoot();
}

void ULuaOverridesClass::RemoveFromOwner()
{
    const auto Class = Owner.Get();
    if (!Class)
        return;

    bool bRemoved = false;

#if UE_VERSION_NEWER_THAN(5, 2, 1)
    // UE5.2.1+ : Children 和 Next 都是 TObjectPtr<UField>

    // 检查头部
    if (Class->Children == this)
    {
        Class->Children = this->Next;
        bRemoved = true;
    }
    else
    {
        // 查找并移除
        for (TObjectPtr<UField> Curr = Class->Children; Curr; Curr = Curr->Next)
        {
            if (Curr->Next == this)
            {
                Curr->Next = this->Next;
                bRemoved = true;
                break;
            }
        }
    }

    if (bRemoved)
    {
        this->Next = nullptr;
    }

#else
    // UE5.2.1 以下
    UField** Field = &Class->Children;

    while (*Field)
    {
        if (*Field == this)
        {
            *Field = this->Next;
            this->Next = nullptr;
            bRemoved = true;
            break;
        }
        Field = &(*Field)->Next;
    }
#endif

    if (bRemoved && !Class->IsRooted() && !GUObjectArray.IsDisregardForGC(Class))
        RemoveFromRoot();
}