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
	//UE��ģ�������ѡ��
	MeshComp->SetSimulatePhysics(true);
	//��ײԤ��ΪPhysicsActor
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;	

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->Radius = 75.0f; //��Χ
	ForceComp->ImpulseStrength = 10.0f; //�����
	ForceComp->bImpulseVelChange = true;  //����������С��UE�г����ٶȱ��

	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
//void AAFPExplosiveBarrel::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// PostInitializeComponents��Actor��ʼ����Ϻ��ٵ���
void AAFPExplosiveBarrel::PostInitializeComponents()
{
	// ִ�иú���ԭ���Ĺ���
	Super::PostInitializeComponents();
	// �󶨵�OnComponentHit�¼���
	MeshComp->OnComponentHit.AddDynamic(this, &AAFPExplosiveBarrel::OnActorHit);
}

void AAFPExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	// log��Ϣ��category��log/warning/error�ȱ�ʾ��־����ϸ�̶ȣ���ӡ����������

	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	UE_LOG(LogTemp, Warning, TEXT("HHHHHHHHHHHHH"));

	FString CombStr = FString::Printf(TEXT("Hit at %s"), *Hit.ImpactPoint.ToString());
	// ��ȡ���磬λ�ã���ӡ�����ݣ���Ҫattach��actor����ɫ������ʱ�䣬�Ƿ���Ӱ��
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombStr, nullptr, FColor::Green, 2.0f, true);
}

// Called every frame
//void AAFPExplosiveBarrel::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}
