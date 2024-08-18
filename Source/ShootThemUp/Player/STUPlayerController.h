// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASTUPlayerController();

	
	void Killed(AController* KillerController, AController* VictimController);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTURespawnComponent* MyRespawnComponent;

protected:

	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	

	void StartRespawn(AController* Controller);
private:
	
	void OnMatchStateChanged(ESTUMathcState State);
};

