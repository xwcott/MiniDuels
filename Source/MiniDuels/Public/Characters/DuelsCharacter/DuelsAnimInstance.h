// MiniDuels code, not copyrighted.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "DuelsAnimInstance.generated.h"

class UDuelsCharacterMovement;
class ADuelsCharacter;
/**
 * 
 */
UCLASS()
class MINIDUELS_API UDuelsAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void OnInit_Implementation() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<ADuelsCharacter> OwningDuelsCharacter = nullptr;
	UPROPERTY()
	TObjectPtr<UDuelsCharacterMovement> DuelsCharacterMovement = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "DuelsAnimInstance")
	bool bIsMoving = false;
	void UpdateIsMoving();
};
