// MiniDuels code, not copyrighted.


#include "Characters/DuelsCharacter/DuelsCharacter.h"

#include "Characters/DuelsCharacter/DuelsCharacterMovement.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ADuelsCharacter::ADuelsCharacter(const FObjectInitializer& ObjectInitializer) : Super
(ObjectInitializer.SetDefaultSubobjectClass<UDuelsCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	if(UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement())
	{
		CharacterMovementComponent->MaxAcceleration = 4096.f;
		CharacterMovementComponent->GroundFriction = 16.f;
	}

	if(UPaperFlipbookComponent* SpriteComp = GetSprite())
	{
		GetSprite()->CastShadow = true;
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 700.f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, -90.f, 0.f));
	SpringArm->bDoCollisionTest = false;

	CamComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CamComponent->SetupAttachment(SpringArm);
}

void ADuelsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DuelsCharacterMappingContext, 0);
		}
		
		if (UEnhancedInputComponent* EnhancedInputComponent =
			CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(
				MoveLeftAction,
				ETriggerEvent::Triggered,
				this,
				&ADuelsCharacter::OnMoveLeftActionTriggered);
			
			EnhancedInputComponent->BindAction(
				MoveRightAction,
				ETriggerEvent::Triggered,
				this,
				&ADuelsCharacter::OnMoveRightActionTriggered);
		}
	}
}

void ADuelsCharacter::OnMoveLeftActionTriggered(const FInputActionValue& InputActionValue)
{
	const bool MoveLeftInput = InputActionValue.Get<bool>();

	GetDuelsCharacterMovement()->UpdateMoveInput(MoveLeftInput ? -1 : 1);
}

void ADuelsCharacter::OnMoveRightActionTriggered(const FInputActionValue& InputActionValue)
{
	const bool MoveLeftInput = InputActionValue.Get<bool>();

	GetDuelsCharacterMovement()->UpdateMoveInput(MoveLeftInput ? 1 : -1);
}

void ADuelsCharacter::BeginPlay()
{
	Super::BeginPlay();

	DuelsCharacterMovement = CastChecked<UDuelsCharacterMovement>(GetCharacterMovement());
	DuelsCharacterMovement->SetOwningDuelsCharacter(this);
}