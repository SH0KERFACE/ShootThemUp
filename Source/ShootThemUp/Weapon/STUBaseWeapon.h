// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;


UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASTUBaseWeapon();
	
	FOnClipEmptySignature OnClipEmpty;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void StartFire(ASTUBaseCharacter* Character);
	
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void StopFire(ASTUBaseCharacter* Character);

	void ChangeClip();
	bool CanReload() const;

	UFUNCTION(BlueprintCallable)
	FWeaponUIData GetUIData() const{return UIData;}

	UFUNCTION(BlueprintCallable)
	FAmmoData GetAmmoData() const{return CurrentAmmo;}

	bool TryToAddAmmo(int32 ClipsAmount);

	UFUNCTION(BlueprintCallable)
	bool IsAmmoEmpty() const;

	UFUNCTION(BlueprintCallable)
	bool IsAmmoFull() const;
protected:

	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* FireSound;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camponents")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 1500.0f;

	UFUNCTION(Blueprintable,BlueprintCallable,BlueprintType)
	virtual void MakeShotdd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{15,10,false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	
	UFUNCTION(BlueprintCallable)
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	UFUNCTION(BlueprintCallable)
	FVector GetMuzzleWorldLocation() const;

	UFUNCTION(BlueprintCallable)
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	UFUNCTION(BlueprintCallable)
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	UFUNCTION(BlueprintCallable)
	void DecreaseAmmo();

	UFUNCTION(BlueprintCallable)
	bool IsClipEmpty() const;

	UFUNCTION(BlueprintCallable)
	UNiagaraComponent* SpawnMuzzleFX();
	
private:
	FAmmoData CurrentAmmo;
};
