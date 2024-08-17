// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement",meta=(ClampMin = "1", ClampMax = "5"))
  float RunModifier = 1.5f;
    virtual float GetMaxSpeed() const override;
};
