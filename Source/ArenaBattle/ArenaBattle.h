// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// 로컬 역할 가져오는 매크로.
#define LOG_LOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))

// 리모트 역할 가져오는 매크로.
#define LOG_REMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))

//로그 매크로 작성
//현재 이 PC가 무슨 모드인지(클라, 스탠드 얼론, 리슨, 데디) 4가지 중 하나
#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? \
		*FString::Printf(TEXT("CLIENT%d"), UE::GetPlayInEditorID()) : \
		((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER")))

//함수 이름이 무엇인지 반환
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)

#define AB_LOG(LogCat, Verbosity, Format, ...) \
	UE_LOG(LogCat, Verbosity, TEXT("[%s][%s/%s] %s %s"), \
		LOG_NETMODEINFO, LOG_LOCALROLEINFO, LOG_REMOTEROLEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

// 로그 카테고리 추가.
DECLARE_LOG_CATEGORY_EXTERN(LogABNetwork, Log, All);



