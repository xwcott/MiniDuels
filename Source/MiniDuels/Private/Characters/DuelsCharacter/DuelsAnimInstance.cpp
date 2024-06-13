// MiniDuels code, not copyrighted.


#include "Characters/DuelsCharacter/DuelsAnimInstance.h"

#include "Characters/DuelsCharacter/DuelsCharacter.h"
#include "Characters/DuelsCharacter/DuelsCharacterMovement.h"

void UDuelsAnimInstance::OnInit_Implementation()
{
	Super::OnInit_Implementation();

	OwningDuelsCharacter = Cast<ADuelsCharacter>(GetOwningActor());
	if(OwningDuelsCharacter)
	{
		DuelsCharacterMovement = Cast<UDuelsCharacterMovement>(OwningDuelsCharacter->GetCharacterMovement());
	}
}

void UDuelsAnimInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!OwningDuelsCharacter || !DuelsCharacterMovement) return;

	UpdateIsMoving();
}

void UDuelsAnimInstance::UpdateIsMoving()
{
	FVector HorizontalVelocity = DuelsCharacterMovement->GetLastUpdateVelocity();
	HorizontalVelocity.Z = 0;
	
	DuelsCharacterMovement->GetMoveInput() != 0.f && HorizontalVelocity.Size() > 0.2f ?
		bIsMoving = true : bIsMoving = false;
}
