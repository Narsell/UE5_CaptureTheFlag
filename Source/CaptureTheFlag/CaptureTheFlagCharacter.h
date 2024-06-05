// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CaptureTheFlagCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AFlag;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACaptureTheFlagCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACaptureTheFlagCharacter();
	
	virtual void Tick(float DeltaTime) override;

	void GrabFlag(AFlag* Flag);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for sprint input */
	void SprintInput(const FInputActionValue& Value);
			
	virtual void Jump() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();


private:

	void RegenerateStamina();

	void ConsumeStamina();

private:

	UPROPERTY(VisibleAnywhere, Category = Flag)
	USceneComponent* FlagSocket;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** SprintInput Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category=Health)
	float LifePoints = 100.f;

	UPROPERTY(EditAnywhere, Category = Stamina)
	float MaxStaminaPoints = 200.f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float MaxSprintSpeed = 600.f;

	UPROPERTY(EditInstanceOnly, Category = Stamina)
	float StaminaPoints = MaxStaminaPoints;

	UPROPERTY(EditAnywhere, Category = Stamina)
	float StaminaRegenRate = 2.0f;

	UPROPERTY(EditAnywhere, Category = Stamina)
	float StaminaConsumptionRate = 1.0f;

	bool bIsSprintInputPressed = false;

	AFlag* ActiveFlag = nullptr;

	FTimerHandle StaminaRegenTimer;

	FTimerHandle StaminaComsumptionTimer;

	// Defined by Movement Component
	float MaxRunningSpeed;

	UCharacterMovementComponent* MovementComponent;

	static TAutoConsoleVariable<int32> CVarCanJump;
};

