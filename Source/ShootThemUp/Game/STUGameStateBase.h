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

	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);

	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;
	
	int32 GetRoundSecondRemaining() const {return RoundCountDown;}
	
	FGameData GetGameData() const {return GameData;}

	virtual void BeginPlay() override;

	
	

		
	
	void GameOver();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;
private:

	void StartRound();
	void GameTimerUpdate();

	
	int32 RoundCountDown = 0;

	
	FTimerHandle GameRoundTimerHandle;
};
