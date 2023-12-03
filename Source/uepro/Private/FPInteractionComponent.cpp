// Fill out your copyright notice in the Description page of Project Settings.


#include "FPInteractionComponent.h"
#include "FPGameplayInterface.h"
#include <DrawDebugHelpers.h>

void UFPInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* MyOwner = GetOwner(); //获取控制角色
	
	FVector EyeLocation; //眼睛位置
	FRotator EyeRotation; //视线方向
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); //将实视线位置方向输出到上面两个变量

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000); //距离1000cm的地方为终点
	

	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	
	TArray<FHitResult> Hits; //检测结果

	float Radius = 30.f;

	FCollisionShape Shape;
	Shape.SetSphere(30.0f);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (const FHitResult &Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor) //判断是否获取到了actor
		{
			// 如果检测到actor不为空，再判断actor有没有实现SurGameplayInterface类
			if (HitActor->Implements<UFPGameplayInterface>())
			{
				//传入为Pawn类型做类型转换
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IFPGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius,32, LineColor, false, 2.0f);
	}
	DrawDebugLine(GetWorld(),  EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);

}

// Sets default values for this component's properties
UFPInteractionComponent::UFPInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFPInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFPInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

