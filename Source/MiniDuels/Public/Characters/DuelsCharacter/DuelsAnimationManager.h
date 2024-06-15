// MiniDuels code, not copyrighted.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DuelsAnimationManager.generated.h"


class ADuelsCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIDUELS_API UDuelsAnimationManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDuelsAnimationManager();

	UFUNCTION()
	ADuelsCharacter* GetOwnerDuelsCharacter() const {return OwningDuelsCharacter;}
	UFUNCTION(BlueprintCallable)
	bool GetLocalWantsToMove() const {return bLocalWantsToMove;}
	
	UFUNCTION()
	void FaceLeft(bool bFaceLeft);
	UFUNCTION()
	void SetWantsToMove(bool bInWantsToMove) {bLocalWantsToMove = bInWantsToMove; ServerUpdateWantsToMove(bInWantsToMove);}
	
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdateSpriteDirection();
	
	UPROPERTY(ReplicatedUsing = OnRep_bIsFacingLeft)
	bool bIsFacingLeft = false;
	UFUNCTION()
	void OnRep_bIsFacingLeft();
	UFUNCTION(Server, Reliable)
	void ServerFaceLeft(bool bFaceLeft);

	UPROPERTY(ReplicatedUsing = OnRep_bWantsToMove)
	bool bWantsToMove = false;
	UPROPERTY()
	bool bLocalWantsToMove = false;
	UFUNCTION()
	void OnRep_bWantsToMove();
	UFUNCTION(Server, Reliable)
	void ServerUpdateWantsToMove(bool bInWantsToMove);
	
	UPROPERTY()
	TObjectPtr<ADuelsCharacter> OwningDuelsCharacter = nullptr;
};