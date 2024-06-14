// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CTFGameState.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CaptureTheFlagCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AFlag;
class ACTFPlayerState;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACaptureTheFlagCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ACaptureTheFlagCharacter();
	
	virtual void Tick(float DeltaTime) override;

	/** Returns the team ID this player belongs to */
	ETeamId GetTeamId() const { return TeamId; }

	/** Returns a pointer to the flag the player is carrying */
	AFlag* GetCarryingFlag() const { return ActiveFlag; }

	/** Makes the player drop the flag in place */
	void DropFlag();

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

	/** Blueprint event to set the appropriate materials/visuals of the actor to match the team */
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void SetTeamColorsEvent(ETeamId InTeamId);

private:

	/** Regenerates a fixed amount of stamina points. */
	void RegenerateStamina();

	/** Consumes a fixed amount of stamina points */
	void ConsumeStamina();

	/** Receives a fixed amount of damage, used for debugging/testing purposes with an input action. */
	void DebugReceiveDamage();

	/** Sets the movement speed to be slow (flag carrier) or normal, depending on the input parameter. */
	void SetSlowMovementSpeed(const bool ReduceMovementSpeed);

	/** Grabs a flag and fixes it to the player */
	void GrabFlag(AFlag* Flag);

	/** 
	 * Prepares the refences required to call the Blueprint Event 'SetTeamColorsEvent' 
	 * Call on or after BeginPlay for it to work.
	 */
	void SetTeamColors();
	
	/** Delegate function call for component begin overlap */
	UFUNCTION()
	void OnOverlapFlag(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	
	/** Team ID this player belongs to */
	UPROPERTY(VisibleInstanceOnly, Category = Team)
	ETeamId TeamId = ETeamId::A;

	/** Current stamina points */
	UPROPERTY(EditInstanceOnly, Category = Stamina)
	float StaminaPoints = MaxStaminaPoints;

	/** Maximum stamina points the player can have */
	UPROPERTY(EditAnywhere, Category = Stamina)
	float MaxStaminaPoints = 200.f;

	/** Stamina regeneration rate */
	UPROPERTY(EditAnywhere, Category = Stamina)
	float StaminaRegenRate = 2.0f;

	/** Stamina consumption rate */
	UPROPERTY(EditAnywhere, Category = Stamina)
	float StaminaConsumptionRate = 1.0f;

	/** Maximum speed the player can reach while sprinting */
	UPROPERTY(EditAnywhere, Category = Movement)
	float MaxSprintSpeed = 600.f;

	/** Percent of the normal player speed applied when the player is carrying a flag. (0 - 1) */
	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 0, ClampMax = 1))
	float FlagCarrierSpeedPercent = 0.8f;

	/** Determines if the player is pressing the sprint input */
	bool bIsSprintInputPressed = false;

	/** Pointer to a potential flag the player could carry */
	AFlag* ActiveFlag = nullptr;

	/** Timer Handle to stamina regeneration timer */
	FTimerHandle StaminaRegenTimer;

	/** Timer Handle to stamina consumption timer */
	FTimerHandle StaminaComsumptionTimer;

	/** 
	 * Maximum speed the player can reach while running
	 * Set by the movement component in BeginPlay so no need to initialize.
	 */
	float MaxRunningSpeed;

	/** Reference to player state instance */
	ACTFPlayerState* PlayerState;

	/* COMPONENT REFERENCES */

	UPROPERTY(VisibleAnywhere, Category = Flag)
	USceneComponent* FlagSocket;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Movement component pointer */
	UCharacterMovementComponent* MovementComponent;

	/* INPUT */

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

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* DebugAction_1;

	/** Console variable to enable/disable jumping */
	static TAutoConsoleVariable<int32> CVarCanJump;
};

