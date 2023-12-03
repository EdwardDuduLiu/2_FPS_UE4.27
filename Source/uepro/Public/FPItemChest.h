// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPGameplayInterface.h"
#include "FPItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class UEPRO_API AFPItemChest : public AActor, public IFPGameplayInterface
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere);
	float TargetPitch;
	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	AFPItemChest();

protected:

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent * BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UStaticMeshComponent * LidMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
