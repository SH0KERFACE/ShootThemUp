// Shoot Them Up Game, All Right Reserved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"
#include "Player/STUPlayerState.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	
	const auto HealthComponent = StuUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = StuUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;
	
	return WeaponComponent->GetWeaponUIData(UIData);	
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = StuUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;
	
	return  WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = StuUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}


void USTUPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
	
}

void USTUPlayerHUDWidget::OnHealthChange(float Health, float HealthDelta)
{
	if(HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
	UpdateHealthBar();
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = StuUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
	if(HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChange);
	}
	UpdateHealthBar();
}

void USTUPlayerHUDWidget::UpdateHealthBar()
{
	if(HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
	}
	
}


int32 USTUPlayerHUDWidget::GetKillsNum() const
{
	const auto Controller = GetOwningPlayer();
	if(!Controller) return 0;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USTUPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
	const int32 MaxLen = 2;
	const TCHAR PrefixSymbol = '0';

	auto BulletStr = FString::FromInt(BulletsNum);
	const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

	if(SymbolsNumToAdd > 0)
	{
		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	}
	return BulletStr;
}
