// MiniDuels code, not copyrighted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DuelsCharacterMovement.generated.h"

class ADuelsCharacter;
/**
 * 
 */
UCLASS()
class MINIDUELS_API UDuelsCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMoveInput() const {return MoveInput;}
	UFUNCTION()
	void SetOwningDuelsCharacter(ADuelsCharacter* InDuelsCharacter) {OwningDuelsCharacter = InDuelsCharacter;}
	UFUNCTION()
	ADuelsCharacter* GetOwnerDuelsCharacter() const {return OwningDuelsCharacter;}

	void UpdateMoveInput(float NewInput);

protected:
	float MoveInput = 0.f;

	void HandleMovement(float DeltaSeconds) const;

	UPROPERTY()
	bool bIsFacingLeft = false;
	UFUNCTION()
	void FlipSprite();

	UPROPERTY()
	TObjectPtr<ADuelsCharacter> OwningDuelsCharacter = nullptr;
};
