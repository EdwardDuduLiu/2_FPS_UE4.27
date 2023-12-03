// Fill out your copyright notice in the Description page of Project Settings.


#include "FPItemChest.h"
#include "Components/StaticMeshComponent.h"

void AFPItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

// Sets default values
AFPItemChest::AFPItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

// Called when the game starts or when spawned
void AFPItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

