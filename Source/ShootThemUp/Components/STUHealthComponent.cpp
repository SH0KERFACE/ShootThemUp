// Shoot Them Up Game, All Right Reserved


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Game/STUGameModeBase.h"


USTUHealthComponent::USTUHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
  
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
	if(IsDead() || IsHealthFull()) return false;

	SetHealth(Health+HealthAmount);
	return true;
}

bool USTUHealthComponent::IsHealthFull() const
{
	return (FMath::IsNearlyEqual(Health, MaxHealth));
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth>0);
	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if(ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}


void USTUHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* InstigatorBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || IsDead() || !GetWorld()) return;
	
	SetHealth(Health - DamageCoef * Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if(IsDead())
	{
		Killed(InstigatorBy);
		OnDeath.Broadcast();
	}
	else if(AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
	PlayCameraShake();
}

void USTUHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if(IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f,  MaxHealth);
	const auto HealthDelta = NextHealth- Health;

	Health = NextHealth;
	Health = FMath::Clamp(NewHealth, 0.0f,  MaxHealth);
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USTUHealthComponent::PlayCameraShake()
{
	if(IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}


void USTUHealthComponent::Killed(AController* KillerController)
{
	if(!GetWorld()) return;
	const auto GameMode =Cast<ASTUGameModeBase>( GetWorld()->GetAuthGameMode());

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}

