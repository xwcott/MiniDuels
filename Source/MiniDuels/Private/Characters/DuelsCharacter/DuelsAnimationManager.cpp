// MiniDuels code, not copyrighted.


#include "Characters/DuelsCharacter/DuelsAnimationManager.h"

#include "Characters/DuelsCharacter/DuelsCharacter.h"
#include "PaperFlipbookComponent.h"
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

void UDuelsAnimationManager::BeginPlay()
{
	Super::BeginPlay();

	OwningDuelsCharacter = CastChecked<ADuelsCharacter>(GetOwner());
}

void UDuelsAnimationManager::FaceLeft(bool bFaceLeft)
{
	ServerFaceLeft_Implementation(bFaceLeft);
	
	bIsFacingLeft = bFaceLeft;
}

void UDuelsAnimationManager::ServerFaceLeft_Implementation(bool bFaceLeft)
{
	if(UPaperFlipbookComponent* FlipbookComponent = OwningDuelsCharacter->GetSprite())
	{
		const FVector CurrentScale = FlipbookComponent->GetRelativeScale3D();
		const FVector NewScale = FVector(CurrentScale.X * bFaceLeft ? -1 : 1, CurrentScale.Y, CurrentScale.Z);
		FlipbookComponent->SetRelativeScale3D(NewScale);

		const FVector CurrentLoc = FlipbookComponent->GetRelativeLocation();
		const FVector NewLoc = FVector(CurrentLoc.X * bFaceLeft ? -1 : 1, CurrentLoc.Y, CurrentLoc.Z);
		FlipbookComponent->SetRelativeLocation(NewLoc);
		
		bIsFacingLeft = bFaceLeft;
	}
}