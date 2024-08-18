// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"



UCLASS()
class SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
public:
	ASTUPlayerCharacter(const FObjectInitializer& ObjInit);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent *SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent *CameraComponent;
protected:
	
	
	UPROPERTY()
	class USphereComponent* CameraCollisionComponent;
	
	virtual void BeginPlay() override;
	virtual void OnDeath() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	
	virtual  bool IsSprinting() const	override;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);


	void OnStartSprinting();
	void OnStopSprinting();

	UFUNCTION()
	void OnCameraCollisionBeginOverlap (UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);

	UFUNCTION()
	void OnCameraCollisionEndOverlap (UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void CheckCameraOverlap();
};
