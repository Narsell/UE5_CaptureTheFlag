// Copyright Epic Games, Inc. All Rights Reserved.

#include "CaptureTheFlagCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Flag.h"
#include "CTFPlayerState.h"
#include "SpawnZone.h"
#include "TeamBase.h"


TAutoConsoleVariable<int32> ACaptureTheFlagCharacter::CVarCanJump(
	TEXT("r.CanJump"),
	1,
	TEXT("Disables/enables the ability to jump on the player character."),
	ECVF_Cheat
);

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACaptureTheFlagCharacter

ACaptureTheFlagCharacter::ACaptureTheFlagCharacter()
	:
	FlagSocket(CreateDefaultSubobject<USceneComponent>(TEXT("FlagSocket"))),
	FollowCamera(CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"))),
	CameraBoom(CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"))),
	MovementComponent(GetCharacterMovement())
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	MovementComponent->bOrientRotationToMovement = true;	
	MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	MovementComponent->JumpZVelocity = 700.f;
	MovementComponent->AirControl = 0.35f;
	MovementComponent->MaxWalkSpeed = 500.f;
	MovementComponent->MinAnalogWalkSpeed = 20.f;
	MovementComponent->BrakingDecelerationWalking = 2000.f;
	MovementComponent->BrakingDecelerationFalling = 1500.0f;

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	FlagSocket->SetupAttachment(RootComponent);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACaptureTheFlagCharacter::OnOverlapFlag);
}

void ACaptureTheFlagCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if(Controller) 
	{
		PlayerState = Controller->GetPlayerState<ACTFPlayerState>();
	}

	MaxRunningSpeed = MovementComponent->MaxWalkSpeed;
	
	SetTeamColors();
}

void ACaptureTheFlagCharacter::RegenerateStamina()
{
	StaminaPoints = FMath::Clamp(StaminaPoints + 10.f, 0.f, MaxStaminaPoints);
}

void ACaptureTheFlagCharacter::ConsumeStamina()
{
	StaminaPoints = FMath::Clamp(StaminaPoints - 20.f, 0.f, MaxStaminaPoints);
}

void ACaptureTheFlagCharacter::TakeDamage()
{
	PlayerState->ReceiveDamage(15.f);
}

void ACaptureTheFlagCharacter::SetReducedMovementSpeed(const bool ReduceMovementSpeed)
{
	MaxSprintSpeed = ReduceMovementSpeed ? MaxSprintSpeed * FlagCarrierSpeedPercent : MaxSprintSpeed / FlagCarrierSpeedPercent;
	MaxRunningSpeed = ReduceMovementSpeed ? MaxRunningSpeed * FlagCarrierSpeedPercent : MaxRunningSpeed / FlagCarrierSpeedPercent;
}

void ACaptureTheFlagCharacter::OnOverlapFlag(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFlag* Flag = Cast<AFlag>(OtherActor);

	if (PlayerState && !PlayerState->IsFlagCarrier() && Flag) {
		GrabFlag(Flag);
	}
}

void ACaptureTheFlagCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float bHasStamina = StaminaPoints > 0.f;

	if (bIsSprintInputPressed && bHasStamina) {
		MovementComponent->MaxWalkSpeed = MaxSprintSpeed;
	}
	else {
		MovementComponent->MaxWalkSpeed = MaxRunningSpeed;	
	}

	if (ActiveFlag) {
		ActiveFlag->SetActorTransform(FlagSocket->GetComponentTransform());
	}

}

void ACaptureTheFlagCharacter::GrabFlag(AFlag* Flag)
{
	ensure(!ActiveFlag && Flag);

	if (!PlayerState) return;

	PlayerState->SetIsFlagCarrier(true);
	SetReducedMovementSpeed(true);
	ActiveFlag = Flag;
	ActiveFlag->SetCarrier(this);

}

void ACaptureTheFlagCharacter::SetTeamColors()
{
	ASpawnZone* SpawnZone = Cast<ASpawnZone>(GetOwner());

	if (SpawnZone && SpawnZone->GetTeamBase())
	{
		TeamId = SpawnZone->GetTeamBase()->GetTeamId();
		SetTeamColorsEvent(TeamId);
	}
}

void ACaptureTheFlagCharacter::DropFlag()
{
	ensure(ActiveFlag);

	if (!PlayerState || !ActiveFlag) return;

	ActiveFlag->OnDropped();

	PlayerState->SetIsFlagCarrier(false);
	SetReducedMovementSpeed(false);
	ActiveFlag = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACaptureTheFlagCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACaptureTheFlagCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACaptureTheFlagCharacter::Look);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACaptureTheFlagCharacter::SprintInput);

		// Debuging
		EnhancedInputComponent->BindAction(DebugAction_1, ETriggerEvent::Triggered, this, &ACaptureTheFlagCharacter::TakeDamage);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACaptureTheFlagCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACaptureTheFlagCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACaptureTheFlagCharacter::SprintInput(const FInputActionValue& Value)
{
	bIsSprintInputPressed = Value.Get<bool>();
	if (bIsSprintInputPressed) {

		if (GetWorldTimerManager().IsTimerActive(StaminaRegenTimer)) {
			GetWorldTimerManager().ClearTimer(StaminaRegenTimer);
		}

		if (!GetWorldTimerManager().IsTimerActive(StaminaComsumptionTimer)) {
			GetWorldTimerManager().SetTimer(StaminaComsumptionTimer, this, &ACaptureTheFlagCharacter::ConsumeStamina, StaminaConsumptionRate, true, 0.f);
		}
	}
	else {

		if (!GetWorldTimerManager().IsTimerActive(StaminaRegenTimer)) {
			GetWorldTimerManager().SetTimer(StaminaRegenTimer, this, &ACaptureTheFlagCharacter::RegenerateStamina, StaminaRegenRate, true, 0.f);
		}

		if (GetWorldTimerManager().IsTimerActive(StaminaComsumptionTimer)) {
			GetWorldTimerManager().ClearTimer(StaminaComsumptionTimer);
		}

	}
}

void ACaptureTheFlagCharacter::Jump()
{
	const int32 CanJump = CVarCanJump.GetValueOnGameThread();
	if (!CanJump) { return; };

	Super::Jump();
	//#ifdef WITH_EDITOR
	//	UE_LOG(LogTemp, Warning, TEXT("JUMPING!"));
	//#endif
}