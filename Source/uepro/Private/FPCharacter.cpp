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
	FRotator ControlRot = GetControlRotation();  //获得控制器的旋转方向
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value); //将rotator转换为vector
}

void AFPCharacter::Moveright(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	// 获取相机（鼠标控制器）的朝向，转向右侧，并朝这个方向移动；传入的Y表示右侧
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void AFPCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AFPCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	//清除定时器
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
	// 获取模型右手位置
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
		// Spawn Transform Matrix， spawn的变换矩阵
		// 朝向角色方向，在角色的中心位置生成
		FTransform SpawnTM = FTransform(GetControlRotation(), RightHandLoc);

		// 参数设置。
		// 此处设置碰撞检测规则为：即使碰撞也总是生成，因为粒子在角色中间生成必然碰撞
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		// 所有能放置或生成的对象都是Actor
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

	//绑定按键动作("UE中调用的名称"；触发的时机如按下或释放；对象；具体方法实现)
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AFPCharacter::PrimaryAttack);

	//绑定跳跃，Charactor类自带
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPCharacter::Jump);

	//
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed,this, &AFPCharacter::PrimaryInteract);
}

