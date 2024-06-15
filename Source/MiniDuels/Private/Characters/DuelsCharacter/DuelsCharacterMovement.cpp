// MiniDuels code, not copyrighted.


#include "Characters/DuelsCharacter/DuelsCharacterMovement.h"

#include "Characters/DuelsCharacter/DuelsAnimationManager.h"
#include "Characters/DuelsCharacter/DuelsCharacter.h"

UDuelsCharacterMovement::UDuelsCharacterMovement()
{
	GroundFriction = 32.f;
	MaxAcceleration = 4096.f;
}

void UDuelsCharacterMovement::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
                                                const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	HandleMovement(DeltaSeconds);
}

void UDuelsCharacterMovement::UpdateMoveInput(float NewInput)
{
	MoveInput += NewInput;
	if(UDuelsAnimationManager* AnimationManager = OwningDuelsCharacter->GetAnimationManager())
	{
		if(MoveInput == 0)
		{
			AnimationManager->SetWantsToMove(false);
			return;
		}
		AnimationManager->FaceLeft(MoveInput < 0);
		AnimationManager->SetWantsToMove(true);
	}
}

void UDuelsCharacterMovement::BeginPlay()
{
	Super::BeginPlay();

	OwningDuelsCharacter = CastChecked<ADuelsCharacter>(GetOwner());
}

void UDuelsCharacterMovement::HandleMovement(float DeltaSeconds) const
{
	if(MoveInput == 0.f) return;

	const FVector ForwardDirection = OwningDuelsCharacter->GetActorForwardVector();
	OwningDuelsCharacter->AddMovementInput(ForwardDirection, MoveInput);
}
