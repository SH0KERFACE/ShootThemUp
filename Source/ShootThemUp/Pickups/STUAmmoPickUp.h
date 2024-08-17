// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickUp.h"

#include "STUAmmoPickUp.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickUp : public ASTUBasePickUp
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	TSubclassOf<class ASTUBaseWeapon> WeaponType;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
