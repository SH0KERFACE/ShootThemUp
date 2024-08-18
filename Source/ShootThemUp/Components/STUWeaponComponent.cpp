// Fill out your copyright notice in the Description page of Project Settings.


#include "STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "Player/STUBaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Animations/STUEQuipFinishedAnimNotify.h"
#include "Animations/STUReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"
constexpr static int32 WeaponNum = 2;

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void USTUWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	
	const auto Character = Cast<ASTUBaseCharacter>(GetOwner());
	
	if (!Character) return;
	OnStartFire.Broadcast(Character);
	CurrentWeapon->StartFire(Character);
}

void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;

	const auto Character = Cast<ASTUBaseCharacter>(GetOwner());
	if (!Character) return;
	
	OnStopFire.Broadcast(Character);
	CurrentWeapon->StopFire(Character);
}

void USTUWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
	EquipWeapon_Server(CurrentWeaponIndex);
}




void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only i% Weapon items"), WeaponNum );
	
	CurrentWeaponIndex = 0;
	SpawnWeapons();
	InitAnimations();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClasses);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmotySocketName);
	}	
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent,
                                               const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}



inline void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("InvaidWeaponIndex"));
		return;
	}
	const auto Character = Cast<ASTUBaseCharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire(Character);
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmotySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].AnimReloadMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
	{
		
		return Data.WeaponClasses == CurrentWeapon->GetClass(); 
	});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EQuipAnimInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass <USTUEQuipFinishedAnimNotify> (EquipAnimMontage);
	if (EquipAnimMontage)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Equip Anim Notify is forgotten to set"));
		checkNoEntry();
	}

	for(auto OneWeaponData : WeaponData)
	{
	
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogTemp, Error, TEXT("Reload Anim Notify is forgotten to set"));
			checkNoEntry();
		}
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
		
	}
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh()) return;

	EQuipAnimInProgress = false;
}

void USTUWeaponComponent::Reload()
{
	ChangeClip();

	Reload_Server();
}

void USTUWeaponComponent::Reload_Server_Implementation()
{
	Reload_Multicast();
}

void USTUWeaponComponent::Reload_Multicast_Implementation()
{
	const auto Character = Cast<ASTUBaseCharacter>(GetOwner());
	if(!Character && Character->IsLocallyControlled()) return;
	
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTUWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if(CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
	
}

bool USTUWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if(CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
	
}

bool USTUWeaponComponent::TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount)
{
	for(const auto Weapon: Weapons)
	{
		if(Weapon && Weapon->IsA(WeaponType))
		{
		
			return Weapon->TryToAddAmmo(ClipsAmount);
			
		}
	}

	return false;
}

bool USTUWeaponComponent::NeedAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType)
{
	for(const auto Weapon: Weapons)
	{
		if(Weapon && Weapon->IsA(WeaponType))
		{
		
			return !Weapon->IsAmmoFull();
			
		}
	}

	return false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComponent != Character->GetMesh()) return;
	
	ReloadAnimInProgress = false;
}

bool USTUWeaponComponent::CanReload() const
{
	 
	return	CurrentWeapon
			&& !EQuipAnimInProgress
			&& !ReloadAnimInProgress
			&& CurrentWeapon->CanReload();
}

void USTUWeaponComponent::OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon)
{
	if(!AmmoEmptyWeapon) return;
	
	if(CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
		Reload_Server();
	}
	else
	{
		for(const auto Weapon: Weapons)
		{
			if(Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
				Reload_Server();
			}
		}
	}

}

void USTUWeaponComponent::ChangeClip()
{
	if(!CanReload()) return;
	const auto Character = Cast<ASTUBaseCharacter>(GetOwner());
	if (!Character) return;
	
	CurrentWeapon->StopFire(Character);
	CurrentWeapon->ChangeClip();	
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTUWeaponComponent::CanFire() const
{
	auto Character = Cast<ASTUBaseCharacter>(GetOwner());
	if (!Character) {return false;}
	
	return CurrentWeapon && !EQuipAnimInProgress && !ReloadAnimInProgress && !Character->IsSprinting();
}

bool USTUWeaponComponent::CanEquip() const
{
	return !EQuipAnimInProgress && !ReloadAnimInProgress;
}

void USTUWeaponComponent::EquipWeapon_Server_Implementation(int32 WeaponIndex)
{
	EquipWeapon_Multicast(WeaponIndex);
}

void USTUWeaponComponent::EquipWeapon_Multicast_Implementation(int32 WeaponIndex)
{
	const auto Character = Cast<ASTUBaseCharacter>(GetOwner());
	if(!Character && Character->IsLocallyControlled()) return;
	
	EquipWeapon(WeaponIndex);
}
