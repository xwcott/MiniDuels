// MiniDuels code, not copyrighted.


#include "Characters/DuelsCharacter/DuelsCharacterMovement.h"

#include "PaperFlipbookComponent.h"
#include "Characters/DuelsCharacter/DuelsCharacter.h"

void UDuelsCharacterMovement::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
                                                const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	HandleMovement(DeltaSeconds);
}

void UDuelsCharacterMovement::FlipSprite()
{
	if(UPaperFlipbookComponent* FlipbookComponent = OwningDuelsCharacter->GetSprite())
	{
		const FVector CurrentScale = FlipbookComponent->GetRelativeScale3D();
		const FVector NewScale = FVector(CurrentScale.X * -1, CurrentScale.Y, CurrentScale.Z);
		FlipbookComponent->SetRelativeScale3D(NewScale);

		const FVector CurrentLoc = FlipbookComponent->GetRelativeLocation();
		const FVector NewLoc = FVector(CurrentLoc.X * -1, CurrentLoc.Y, CurrentLoc.Z);
		FlipbookComponent->SetRelativeLocation(NewLoc);
		
		bIsFacingLeft = !bIsFacingLeft;
	}
}

void UDuelsCharacterMovement::UpdateMoveInput(float NewInput)
{
	MoveInput += NewInput;
	
	if ((MoveInput < 0 && !bIsFacingLeft) || (MoveInput > 0 && bIsFacingLeft))
	{
		FlipSprite();
	}
}

void UDuelsCharacterMovement::HandleMovement(float DeltaSeconds) const
{
	if(MoveInput == 0.f) return;

	const FVector ForwardDirection = OwningDuelsCharacter->GetActorForwardVector();
	OwningDuelsCharacter->AddMovementInput(ForwardDirection, MoveInput);
}