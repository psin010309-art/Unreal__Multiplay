// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ABFountain.h"
#include <ArenaBattle.h>

#include "Components/StaticMeshComponent.h"
#include <Net/UnrealNetwork.h>
#include <Components/PointLightComponent.h>
#include <EngineUtils.h>

// Sets default values
AABFountain::AABFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));

	RootComponent = Body;
	Water->SetupAttachment(Body);
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 132.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'"));
	if (BodyMeshRef.Object)
	{
		Body->SetStaticMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WaterMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02'"));
	if (WaterMeshRef.Object)
	{
		Water->SetStaticMesh(WaterMeshRef.Object);
	}

	//리플리케이션 옵션 활성화.
	//bReplicates = true;
	SetReplicates(true);

	//네트워크 빈도 설정(1초에 1번)
	//NetUpdateFrequency = 1.0f;
	SetNetUpdateFrequency(1.0f);

	//연관성 판정 거리값 설정(NetCullDistanceSquared)
	//20미터임. -> 20m * 20m
	SetNetCullDistanceSquared(4000000.0f);

	//휴면 상태로 설정
	//SetNetDormancy(DORM_Initial);
}

// Called when the game starts or when spawned
void AABFountain::BeginPlay()
{
	Super::BeginPlay();

	//타이머를 활용해 반복 로직 실행
	if (HasAuthority())
	{
		//FTimerHandle Handle;
		//GetWorld()->GetTimerManager().SetTimer(
		//	Handle,
		//	FTimerDelegate::CreateLambda([&]()
		//		{
		//			//ServerRotationYaw += 1.0f;

		//			//데이터 설정
		//			//BigData.Init(BigDataElement, 1000);

		//			//데이터 요소 값 업데이트
		//			//BigDataElement += 1.0f;

		//			//랜덤으로 색상 값 선택
		//			//ServerLightColor = FLinearColor(
		//			//	FMath::RandRange(0.0f, 1.0f),
		//			//	FMath::RandRange(0.0f, 1.0f),
		//			//	FMath::RandRange(0.0f, 1.0f)
		//			//);

		//			////서버에서는 OnRep_ 콜백 함수가 자동 실행되지 않음.
		//			////따라서 필요 시에는 명시적으로 호출해야함.
		//			//OnRep_ServerLightColor();

		//			//멀티캐스트 RPC로 전달할 색상 값.
		//			//const FLinearColor NewLightColor = FLinearColor(
		//			//		FMath::RandRange(0.0f, 1.0f),
		//			//		FMath::RandRange(0.0f, 1.0f),
		//			//		FMath::RandRange(0.0f, 1.0f)
		//			//	);

		//			////멀티캐스트 RPC로 호출(서버에서 호출)
		//			////->서버 포함 모든 클라에서 _Implementation함수 실행.
		//			////MulticastRPCChangeLightColor(NewLightColor);

		//			////클라 RPC호출(서버에서 호출)
		//			//ClientRPCChangeLightColor(NewLightColor);
		//		}
		//	), 1.0f, true
		//);

		////두번째 타이머: 휴면 상태 깨우는 데 사용.
		//FTimerHandle Handle2;
		//GetWorld()->GetTimerManager().SetTimer(
		//	Handle2,
		//	FTimerDelegate::CreateLambda([&]()
		//		{
		//			//깨우기
		//			//FlushNetDormancy();

		//			//접속한 클라의 플레이어 컨트롤러 가져오기.
		//			//for (auto Iterator = GetWorld()->GetPlayerControllerIterator();
		//			//	Iterator;
		//			//	++Iterator)
		//			//{
		//			//	//이터레이터 플레이어 컨트롤러 가져오기
		//			//	APlayerController* PlayerController = Iterator->Get();

		//			//	//리슨 서버 입장에서 같은 머신에 있는 클라이언트가 아닌지 확인.
		//			//	if (PlayerController && !PlayerController->IsLocalPlayerController())
		//			//	{
		//			//		//첫 번째 플레이어 컨트롤러에 오너십 설정.
		//			//		SetOwner(PlayerController);
		//			//		break;
		//			//	}
		//			//}

		//			//Ranged-Based Loop 활용
		//			//for (APlayerController* PlayerController : TActorRange<APlayerController>(GetWorld()))
		//			//{
		//			//		if (PlayerController && !PlayerController->IsLocalPlayerController())
		//			//	{
		//			//		//첫 번째 플레이어 컨트롤러에 오너십 설정.
		//			//		SetOwner(PlayerController);
		//			//		break;
		//			//	}
		//			//}
		//		}
		//	), 10.0f, false //10초 있다가 실행.
		//);

		////프로퍼티 리플리케이션 방식으로 라이트 변경
		//FTimerHandle Handle3;
		//GetWorld()->GetTimerManager().SetTimer(
		//	Handle3,
		//	FTimerDelegate::CreateLambda([&]()
		//		{
		//			//랜덤으로 색상 값 선택
		//			//ServerLightColor = FLinearColor(
		//			//	FMath::RandRange(0.0f, 1.0f),
		//			//	FMath::RandRange(0.0f, 1.0f),
		//			//	FMath::RandRange(0.0f, 1.0f)
		//			//);

		//			////서버에서는 OnRep_ 콜백 함수가 자동 실행되지 않음.
		//			////따라서 필요 시에는 명시적으로 호출해야함.
		//			//OnRep_ServerLightColor();

		//			const FLinearColor NewLightColor = FLinearColor(
		//				FMath::RandRange(0.0f, 1.0f),
		//				FMath::RandRange(0.0f, 1.0f),
		//				FMath::RandRange(0.0f, 1.0f)
		//			);

		//			MulticastRPCChangeLightColor(NewLightColor);
		//		}
		//	), 5.0f, false
		//);
	}
	//클라이언트
	else
	{
		//오너십 설정
		// 클라쪽에서 OwnerShip설정은 하면안됨.
		//SetOwner(GetWorld()->GetFirstPlayerController());

		//클라이언트에서 서버 RPC함수 호출
		//FTimerHandle Handle;
		//GetWorld()->GetTimerManager().SetTimer(
		//	Handle,
		//	FTimerDelegate::CreateLambda([&]()
		//		{
		//			//ServerRPCChangeLightColor();
		//		}
		//	), 1.0f, true
		//);
	}
}

void AABFountain::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//리플리케이션 대상 속성 추가.
	DOREPLIFETIME(AABFountain, ServerRotationYaw);
	//DOREPLIFETIME(AABFountain, BigData);
	DOREPLIFETIME(AABFountain, ServerLightColor);
	//DOREPLIFETIME_CONDITION(AABFountain, ServerLightColor, COND_InitialOnly);
}

//데이터와 커넥션(연결 통로) 모두 전달
//inline void AABFountain::OnActorChannelOpen(FInBunch& InBunch, UNetConnection* Connection) 
//{
//
//
//	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
//
//	Super::OnActorChannelOpen(InBunch, Connection);
//
//	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
//}
//
//bool AABFountain::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
//{
//	bool Result = Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
//	
//	if (false == Result)
//	{
//		AB_LOG(LogABNetwork, Log, TEXT("Not Relevan! [%s] %s"), *RealViewer->GetName(), *SrcLocation.ToCompactString());
//	}
//
//	return Result;
//}
//
//void AABFountain::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
//{
//	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
//
//	Super::PreReplication(ChangedPropertyTracker);
//}

// Called every frame
void AABFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//서버 / 클라 로직 구분해서 구현.
	//->이 액터가 어디에 있는지를 구분해야함.
	//HasAuthority서버인지 확인(true면 서버)
	if (HasAuthority())
	{
		//회전 적용
		AddActorLocalRotation(FRotator(0.0f, RotationRate * DeltaTime, 0.0f));

		//변경된 회전 값을 복제(리플리케이션)되는 변수에 설정.
		//루트 컴포넌트 Transform은 액터의 Transform과 같음
		ServerRotationYaw = RootComponent->GetComponentRotation().Yaw;

	}
	else //클라
	{
		//서버로부터 데이터를 받은 이후에 경과한 시간 기록.
		ClientTimeSinceUpdate += DeltaTime;

		//서버로부터 데이터를 받은 이후에 경과한 시간이 얼마 안됐으면 종료.
		if (ClientTimeBetweenLastUpdate < KINDA_SMALL_NUMBER)
		{
			return;
		}

		//회전 예측 값 - 다음에 전달 받을 회전의 예측 값.
		const float EstimateRotationYaw = ServerRotationYaw + RotationRate * ClientTimeBetweenLastUpdate;

		//보간 시간 계산(t또는 alpha)
		const float LerpRatio = ClientTimeSinceUpdate / ClientTimeBetweenLastUpdate;

		//클라이언트 보간.
		const float ClientNewYaw = FMath::Lerp(ServerRotationYaw, EstimateRotationYaw, LerpRatio);

		FRotator ClientRotator = RootComponent->GetComponentRotation();
		ClientRotator.Yaw = ClientNewYaw;

		//회전 값 설정
		RootComponent->SetWorldRotation(ClientRotator);
	}

}

void AABFountain::OnRep_ServerRotationYaw()
{
	//로그 출력.
	//AB_LOG(LogABNetwork, Log, TEXT("Yaw: %f"), ServerRotationYaw);

	//서버로부터 전달받은 "변경된 회전 값"을 적용.
	FRotator NewRotator = RootComponent->GetComponentRotation();

	//Yaw회전 값은 서버로 부터 전달받은 값 설정.
	NewRotator.Yaw = ServerRotationYaw;

	//루트 컴포넌트에 회전 설정.
	RootComponent->SetWorldRotation(NewRotator);

	//시간 갱신
	ClientTimeBetweenLastUpdate = ClientTimeSinceUpdate;

	//경과 시간 초기화.
	ClientTimeSinceUpdate = 0.0f;
}

void AABFountain::OnRep_ServerLightColor()
{
	//서버가 아닌 경우, 전달된 값 출력.
	if (!HasAuthority())
	{
		AB_LOG(LogABNetwork, Log, TEXT("LightColor: %s"), *ServerLightColor.ToString());
	}
	
	//컴포넌트를 검색해서 전달 받은(또는 변경한) 라이트 색상 설정.
	UPointLightComponent* PointLight = GetComponentByClass<UPointLightComponent>();
	if (nullptr != PointLight)
	{
		PointLight->SetLightColor(ServerLightColor);
	}
}

void AABFountain::ClientRPCChangeLightColor_Implementation(const FLinearColor& NewLightColor)
{
	//서버가 아닌 경우, 전달된 값 출력.
	AB_LOG(LogABNetwork, Log, TEXT("LightColor: %s"), *NewLightColor.ToString());

	//컴포넌트를 검색해서 전달 받은(또는 변경한) 라이트 색상 설정.
	UPointLightComponent* PointLight = GetComponentByClass<UPointLightComponent>();
	if (nullptr != PointLight)
	{
		PointLight->SetLightColor(NewLightColor);
	}
}

bool AABFountain::ServerRPCChangeLightColor_Validate()
{
	//false반환 시 검증 실패
	//검증에 성공 시 true반환
	return true;
}

void AABFountain::ServerRPCChangeLightColor_Implementation()
{
	//이 로직은 서버에서 실행됨.
	//멀티캐스트 RPC로 전달할 색상 값.
	const FLinearColor NewLightColor = FLinearColor(
			FMath::RandRange(0.0f, 1.0f),
			FMath::RandRange(0.0f, 1.0f),
			FMath::RandRange(0.0f, 1.0f)
		);
	//멀티캐스트 RPC로 호출(서버에서 호출)
	//->서버 포함 모든 클라에서 _Implementation함수 실행.
	MulticastRPCChangeLightColor(NewLightColor);
}

void AABFountain::MulticastRPCChangeLightColor_Implementation(const FLinearColor& NewLightColor)
{
	//구현부는 만들지 않고 호출용으로만
	//서버가 아닌 경우, 전달된 값 출력.
	AB_LOG(LogABNetwork, Log, TEXT("LightColor: %s"), *NewLightColor.ToString());

	//컴포넌트를 검색해서 전달 받은(또는 변경한) 라이트 색상 설정.
	UPointLightComponent* PointLight = GetComponentByClass<UPointLightComponent>();
	if (nullptr != PointLight)
	{
		PointLight->SetLightColor(NewLightColor);
	}
}



