// MiniDuels code, not copyrighted.


#include "Characters/DuelsCharacter/DuelsAnimationManager.h"

#include "Characters/DuelsCharacter/DuelsCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Characters/DuelsCharacter/DuelsCharacterMovement.h"
#include "Net/UnrealNetwork.h"

UDuelsAnimationManager::UDuelsAnimationManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicated(true);
}

void UDuelsAnimationManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDuelsAnimationManager, bIsFacingLeft);
}

void UDuelsAnimationManager::UpdateSpriteDirection()
{
	if (UPaperFlipbookComponent* FlipbookComponent = OwningDuelsCharacter->GetSprite())
	{
		const FVector CurrentScale = FlipbookComponent->GetRelativeScale3D();
		const FVector NewScale = FVector(bIsFacingLeft ? -1.f : 1.f, CurrentScale.Y, CurrentScale.Z);
		if(CurrentScale == NewScale) return;
		FlipbookComponent->SetRelativeScale3D(NewScale);

		const FVector CurrentLoc = FlipbookComponent->GetRelativeLocation();
		const FVector NewLoc = FVector(CurrentLoc.X * -1.f, CurrentLoc.Y, CurrentLoc.Z);
		FlipbookComponent->SetRelativeLocation(NewLoc);
	}
}

void UDuelsAnimationManager::BeginPlay()
{
	Super::BeginPlay();

	OwningDuelsCharacter = CastChecked<ADuelsCharacter>(GetOwner());
}

void UDuelsAnimationManager::OnRep_bIsFacingLeft()
{
	if(GetOwnerRole() == ROLE_AutonomousProxy) return;
	
	float MoveInput = OwningDuelsCharacter->GetDuelsCharacterMovement()->GetMoveInput();
	if(MoveInput != 0) bIsFacingLeft = MoveInput < 0;
	UpdateSpriteDirection();
}

void UDuelsAnimationManager::ServerFaceLeft_Implementation(bool bFaceLeft)
{
	bIsFacingLeft = bFaceLeft;
	UpdateSpriteDirection();
}

void UDuelsAnimationManager::FaceLeft(const bool bFaceLeft)
{
	bIsFacingLeft = bFaceLeft;
	UpdateSpriteDirection();
	
	if (!GetOwner()->HasAuthority())
	{
		ServerFaceLeft(bFaceLeft);
	}
}