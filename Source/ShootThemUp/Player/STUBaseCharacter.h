// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "STUBaseCharacter.generated.h"

class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ASTUBaseCharacter(const FObjectInitializer &ObjInit);

protected:
  

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  class USTUHealthComponent* HealthComponent;
  
  UPROPERTY( BlueprintReadWrite, Category = "Components")
  class USTUWeaponComponent* WeaponComponent;
  
  
  UPROPERTY(EditDefaultsOnly, Category = "Animation")
  UAnimMontage* DeathAnimMontage;
  
  UPROPERTY(EditDefaultsOnly, Category = "Damage")
  FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

  UPROPERTY(EditDefaultsOnly, Category = "Damage")
  FVector2D LandedDamage = FVector2D(10.0f, 100.0f);


  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
  USoundCue* DeathSound;
  
  virtual void BeginPlay() override;
  virtual void OnDeath();
  virtual void OnHealthChanged(float Health, float HealthDelta);
public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
 

  UFUNCTION(BlueprintCallable, Category = "Movement")
  virtual  bool IsSprinting() const;

  UFUNCTION(BlueprintCallable, Category = "Movement")
  float GetMovementDirection() const;

private:
 
 

  UFUNCTION()
  void OnGroundLanded(const FHitResult& Hit);

  
}; 