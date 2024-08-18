// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "Player/STUBaseCharacter.h"
#include "STUWeaponComponent.generated.h"



UCLASS( ClassGroup=(Custom),Blueprintable, meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartFire, ASTUBaseCharacter*, Character);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStopFire, ASTUBaseCharacter*, Character);
	
	UPROPERTY(BlueprintAssignable)
	FOnStartFire OnStartFire;
	
	UPROPERTY(BlueprintAssignable)
	FOnStopFire OnStopFire;
	USTUWeaponComponent();
	
	
	virtual void StartFire();
	
	void StopFire();
	
	virtual void NextWeapon();
	
	void Reload();

	UFUNCTION(Reliable, Server)
	void Reload_Server();

	UFUNCTION(Reliable, NetMulticast)
	void Reload_Multicast();
	
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount);
	bool NeedAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType);

	

protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	int32 CurrentWeaponIndex = 0;
	
	UPROPERTY(BlueprintReadOnly)
	ASTUBaseWeapon* CurrentWeapon = nullptr;
	
	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmotySocketName = "ArmorySocket";
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* EquipAnimMontage;

	bool CanFire() const;
	bool CanEquip() const;

	void EquipWeapon(int32 WeaponIndex);
	
	UFUNCTION(Reliable, Server)
	void EquipWeapon_Server(int32 WeaponIndex);

	UFUNCTION(Reliable, NetMulticast)
	void EquipWeapon_Multicast(int32 WeaponIndex);
private:
	
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	
	bool EQuipAnimInProgress = false;

	bool ReloadAnimInProgress = false;
	
	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	

	void PlayAnimMontage(UAnimMontage* Animation);
	
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	
	bool CanReload() const;

	void OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon);
	void ChangeClip();
	
	
};



