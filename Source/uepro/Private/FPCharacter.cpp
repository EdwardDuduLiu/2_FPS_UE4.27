// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "FPInteractionComponent.h"

// Sets default values
AFPCharacter::AFPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true; //decide wheather spring uses pawncontrolrotation
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UFPInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<UAttributesComponent>("AttributeComp");




	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;  //decide wheather pawn uses controllerrotation
}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPCharacter::Moveforward(float value)
{
	FRotator ControlRot = GetControlRotation();  //��ÿ���������ת����
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value); //��rotatorת��Ϊvector
}

void AFPCharacter::Moveright(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	// ��ȡ����������������ĳ���ת���Ҳ࣬������������ƶ��������Y��ʾ�Ҳ�
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void AFPCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AFPCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	//�����ʱ��
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
	// ��ȡģ������λ��
}

void AFPCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
	
}

void AFPCharacter::PrimaryAttack_TimeElapsed()
{
	if (ensure(ProjectileClass))
	{
		FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");
		// Spawn Transform Matrix�� spawn�ı任����
		// �����ɫ�����ڽ�ɫ������λ������
		FTransform SpawnTM = FTransform(GetControlRotation(), RightHandLoc);

		// �������á�
		// �˴�������ײ������Ϊ����ʹ��ײҲ�������ɣ���Ϊ�����ڽ�ɫ�м����ɱ�Ȼ��ײ
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		// �����ܷ��û����ɵĶ�����Actor
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//bind move(forward back)
	PlayerInputComponent->BindAxis("Moveforward", this, &AFPCharacter::Moveforward);
	//bind move(right left)
	PlayerInputComponent->BindAxis("Moveright", this, &AFPCharacter::Moveright);

	//bind turn-yaw direction 
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//bind turn-pitch direction
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	//�󶨰�������("UE�е��õ�����"��������ʱ���簴�»��ͷţ����󣻾��巽��ʵ��)
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AFPCharacter::PrimaryAttack);

	//����Ծ��Charactor���Դ�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPCharacter::Jump);

	//
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed,this, &AFPCharacter::PrimaryInteract);
}

