// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "STUBasePickUp.generated.h"



UCLASS()
class SHOOTTHEMUP_API ASTUBasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBasePickUp();

protected:
	UPROPERTY(VisibleAnywhere, Category = "PickUp")
	class USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	bool bIsSpin = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	bool CouldBeTakenTest = true;
	
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;
	
private:
	float RotationYaw = 0.0f;

	FTimerHandle RespawnTimerHandle;
	
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();
};
