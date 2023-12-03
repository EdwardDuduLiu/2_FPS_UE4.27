// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "AttributesComponent.h"
#include "FPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UFPInteractionComponent;
class UAnimMontage;
class UAttributesComponent;

UCLASS()
class UEPRO_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	// 投射体子类
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

public:
	// Sets default values for this character's properties
	AFPCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;  //pretell a spring

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;  //pretell a camera

	UPROPERTY(VisibleAnywhere)
	UFPInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributesComponent* AttributeComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Moveforward
	void Moveforward(float value);

	//Moveright
	void Moveright(float value);

	void PrimaryAttack();

	void PrimaryInteract();

	void PrimaryAttack_TimeElapsed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
