// Fill out your copyright notice in the Description page of Project Settings.


#include "AFPExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAFPExplosiveBarrel::AAFPExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//UE中模拟物理的选项
	MeshComp->SetSimulatePhysics(true);
	//碰撞预设为PhysicsActor
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;	

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->Radius = 75.0f; //范围
	ForceComp->ImpulseStrength = 10.0f; //冲击力
	ForceComp->bImpulseVelChange = true;  //忽略质量大小。UE中冲量速度变更

	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
//void AAFPExplosiveBarrel::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// PostInitializeComponents在Actor初始化完毕后再调用
void AAFPExplosiveBarrel::PostInitializeComponents()
{
	// 执行该函数原本的功能
	Super::PostInitializeComponents();
	// 绑定到OnComponentHit事件上
	MeshComp->OnComponentHit.AddDynamic(this, &AAFPExplosiveBarrel::OnActorHit);
}

void AAFPExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	// log信息的category，log/warning/error等表示日志的详细程度，打印的文字内容

	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	UE_LOG(LogTemp, Warning, TEXT("HHHHHHHHHHHHH"));

	FString CombStr = FString::Printf(TEXT("Hit at %s"), *Hit.ImpactPoint.ToString());
	// 获取世界，位置，打印的内容，需要attach的actor，颜色，持续时间，是否有影子
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombStr, nullptr, FColor::Green, 2.0f, true);
}

// Called every frame
//void AAFPExplosiveBarrel::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}
