// Shoot Them Up Game, All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "STUCoreTypes.h"
#include "STUGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameStateBase : public AGameStateBase
{
	
	GENERATED_BODY()

public:

	FOnMatchStateChangedSignature OnMatchStateChanged;

	void SetMatchState(ESTUMathcState State);

private:
	ESTUMathcState MatchState = ESTUMathcState::WaitingToStart;
};
