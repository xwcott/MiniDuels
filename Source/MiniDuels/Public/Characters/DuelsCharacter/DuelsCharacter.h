// MiniDuels code, not copyrighted.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DuelsCharacter.generated.h"

class UDuelsAnimationManager;
struct FInputActionValue;
class UDuelsCharacterMovement;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class MINIDUELS_API ADuelsCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ADuelsCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDuelsCharacterMovement* GetDuelsCharacterMovement() const {return DuelsCharacterMovement;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDuelsAnimationManager* GetAnimationManager() const {return AnimationManager;}

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CamComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UDuelsAnimationManager> AnimationManager;
	
	UPROPERTY()
	TObjectPtr<UDuelsCharacterMovement> DuelsCharacterMovement = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess=true))
	TObjectPtr<UInputMappingContext> DuelsCharacterMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess=true))
	TObjectPtr<UInputAction> MoveLeftAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess=true))
	TObjectPtr<UInputAction> MoveRightAction;
	
	void OnMoveLeftActionTriggered(const FInputActionValue& InputActionValue);
	void OnMoveRightActionTriggered(const FInputActionValue& InputActionValue);
};