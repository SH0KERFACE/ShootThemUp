// Shoot Them Up Game, All Right Reserved


#include "Pickups/STUAmmoPickUp.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickUp::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = StuUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;
	
	const auto WeaponComponent = StuUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
	if(!WeaponComponent) return false;
	
	UE_LOG(LogAmmoPickup, Display, TEXT("Pickup was taken"));
	

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
