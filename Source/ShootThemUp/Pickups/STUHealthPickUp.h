#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickUp.h"
#include "STUHealthPickUp.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickUp : public ASTUBasePickUp
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "1000"))
	float HealAmount = 100.f;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
