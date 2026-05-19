// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "DS_EnumTypes.h"
#include "DedicatedServers/DedicatedServers.h"
#include "DS_StructTypes.generated.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/
#define IMPLEMENT_DUMPABLE_STRUCT(StructType) \
virtual const UScriptStruct* GetScriptStruct() const override \
{ \
return StructType::StaticStruct(); \
}

USTRUCT()
struct FDS_DumpableStruct
{
	GENERATED_BODY()
	virtual ~FDS_DumpableStruct() = default;

void Dump() const
{
    const UScriptStruct* ScriptStruct = GetScriptStruct();
    if (!ScriptStruct) return;
	
    UE_LOG(LogDedicatedServers, Log, TEXT(" %s: "), *ScriptStruct->GetName());
	
    for (TFieldIterator<FProperty> It(ScriptStruct); It; ++It)
    {
        FProperty* Prop = *It; 
        const void* ValuePtr = Prop->ContainerPtrToValuePtr<void>(this);
    	
        FString ValueStr;
        Prop->ExportTextItem_Direct(ValueStr, ValuePtr, nullptr, nullptr, PPF_None);
        UE_LOG(LogDedicatedServers, Log, TEXT("  %s: %s"), *Prop->GetName(), *ValueStr);
    }
}

	virtual const UScriptStruct* GetScriptStruct() const
	{
		return nullptr;
	}
};


USTRUCT(BlueprintType)
struct FDS_CountdownTimerHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EDS_CountdownTimerState State = EDS_CountdownTimerState::NotStarted;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EDS_CountdownTimerType Type = EDS_CountdownTimerType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CountdownTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CountdownUpdateInterval = 1.0f;

	FTimerHandle TimerFinishedHandle{};
	FTimerHandle TimerUpdateHandle{};
	FTimerDelegate TimerFinishedDelegate{};
	FTimerDelegate TimerUpdateDelegate{};
};

inline bool operator==(const FDS_CountdownTimerHandle& lhs, const FDS_CountdownTimerHandle& rhs)
{
	return lhs.Type == rhs.Type;
}
/*-------------------------------------------------------------------------*/