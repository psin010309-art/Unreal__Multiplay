// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABFountain.generated.h"

UCLASS()
class ARENABATTLE_API AABFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void OnActorChannelOpen(class FInBunch& InBunch, class UNetConnection* Connection);

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Water;

	//속성 변경됐을 때 호출될 콜백 함수.
	//->클라이언트에서 값이 변경될 때 호출.
	UFUNCTION()
	void OnRep_ServerRotationYaw();

	//서버에서 액터를 돌릴건데 그 값을 복제하라고 지정
	//콜백 등록
	UPROPERTY(ReplicatedUsing = OnRep_ServerRotationYaw)
	float ServerRotationYaw;

	// 회전 속도.
	float RotationRate = 30.0f;

	//보간을 위해 추가 변수 선언
	//서버로부터 데이터를 받은 후에 시간이 얼마나 경과했는지를 기록.
	float ClientTimeSinceUpdate = 0.0f;

	//서버로 부터 데이터를 받고, 그 다음 데이터를 받았을 떄까지 걸린 시간.
	float ClientTimeBetweenLastUpdate = 0.0f;

};
