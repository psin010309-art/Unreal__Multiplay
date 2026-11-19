// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameMode.h"
#include "ABGameMode.h"
#include "Player/ABPlayerController.h"

//이 모양이 최근 CPP에서 권장하는 인클루드 구문
//따옴표는 같은 경로에 있는 헤더 인클루드할 때 사용하기를 권장.
#include <ArenaBattle.h>

AABGameMode::AABGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/ArenaBattle/Blueprint/BP_ABCharacterPlayer.BP_ABCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void AABGameMode::OnPlayerDead()
{

}

void AABGameMode::PreLogin(
	const FString& Options, 
	const FString& Address, 
	const FUniqueNetIdRepl& UniqueId, 
	FString& ErrorMessage)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

APlayerController* AABGameMode::Login(
	UPlayer* NewPlayer, 
	ENetRole InRemoteRole, 
	const FString& Portal, 
	const FString& Options, 
	const FUniqueNetIdRepl& UniqueId, 
	FString& ErrorMessage)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
	return NewPlayerController;
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostLogin(NewPlayer);
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABGameMode::StartPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::StartPlay();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}
