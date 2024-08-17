// Shoot Them Up Game, All Right Reserved


#include "Pickups/STUHealthPickUp.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);


bool ASTUHealthPickUp::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = StuUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->TryToAddHealth(HealAmount);
}
