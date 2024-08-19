// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class ASTUGameStateBase;
class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

	

	
protected:

	virtual void OnPossess(APawn* InPawn) override;
	
};

