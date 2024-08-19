// Shoot Them Up Game, All Right Reserved


#include "Game/STUGameStateBase.h"


void ASTUGameStateBase::BeginPlay()
{
	Super::BeginPlay();

    
	StartRound();
 
}

void ASTUGameStateBase::GameTimerUpdate()
{
    
	if(--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
		
		GameOver();
		
	}
}



void ASTUGameStateBase::GameOver()
{
	OnGameOver.Broadcast();
}



void ASTUGameStateBase::StartRound()
{
	RoundCountDown = GameData.RoundsTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameStateBase::GameTimerUpdate, 1.0f, true);
}
