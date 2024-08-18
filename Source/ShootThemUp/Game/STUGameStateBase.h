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

	void RespawnRequest(AController* Controller);

	
	int32 GetCurrentRoundNum() const {return CurrenRound;}
	int32 GetRoundSecondRemaining() const {return RoundCountDown;}
	
	FGameData GetGameData() const {return GameData;}

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	int MinRoundTimeForRespawn = 10;

	int32 CurrenRound = 1;
	int32 RoundCountDown = 0;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;
private:
	ESTUMathcState MatchState = ESTUMathcState::WaitingToStart;

	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	

	void GameOver();

	
	FTimerHandle GameRoundTimerHandle;
};
