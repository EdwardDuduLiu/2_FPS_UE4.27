// Fill out your copyright notice in the Description page of Project Settings.


#include "FPInteractionComponent.h"
#include "FPGameplayInterface.h"
#include <DrawDebugHelpers.h>

void UFPInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* MyOwner = GetOwner(); //��ȡ���ƽ�ɫ
	
	FVector EyeLocation; //�۾�λ��
	FRotator EyeRotation; //���߷���
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); //��ʵ����λ�÷��������������������

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000); //����1000cm�ĵط�Ϊ�յ�
	

	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	
	TArray<FHitResult> Hits; //�����

	float Radius = 30.f;

	FCollisionShape Shape;
	Shape.SetSphere(30.0f);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (const FHitResult &Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor) //�ж��Ƿ��ȡ����actor
		{
			// �����⵽actor��Ϊ�գ����ж�actor��û��ʵ��SurGameplayInterface��
			if (HitActor->Implements<UFPGameplayInterface>())
			{
				//����ΪPawn����������ת��
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

