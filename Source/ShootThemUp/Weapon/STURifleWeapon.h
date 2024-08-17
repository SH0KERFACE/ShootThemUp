// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	ASTURifleWeapon();

	
	virtual void StartFire() ;

	
	virtual void StopFire() ;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float TimeBetwenShots = 0.1f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamagedAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UNiagaraSystem* TraceFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "Trace Target";
	
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USTUWeaponFXComponent* WeaponFXComponent;

	virtual void BeginPlay() override;
	virtual void MakeShotdd() override;

	
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const  override;
	

	UPROPERTY(BlueprintReadWrite)
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* FireAudioComponent;
private:
	FTimerHandle ShotTimerHandle;

	
	
	void MakeDamage(const FHitResult& HitResult);

	
	void InitFX();

	
	void SetFXActive(bool IsActive);


	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	AController* GetController() const;
};

