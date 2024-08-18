// Shoot Them Up Game, All Right Reserved


#include "Game/STUGameStateBase.h"


void ASTUGameStateBase::BeginPlay()
{
	Super::BeginPlay();

    
    
	CurrenRound = 1;
	StartRound();
 
}

void ASTUGameStateBase::GameTimerUpdate()
{
    
	if(--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
		if(CurrenRound + 1 <= GameData.RoundsNum)
		{
			++CurrenRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASTUGameStateBase::ResetPlayers()
{
	if(!GetWorld()) return;

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASTUGameStateBase::ResetOnePlayer(AController* Controller)
{
	if(Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
    
	
    
}


void ASTUGameStateBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}



void ASTUGameStateBase::GameOver()
{

		//	Pawn->TurnOff();
		//	Pawn->DisableInput(nullptr);
		
}

void ASTUGameStateBase::SetMatchState(ESTUMathcState State)
{
	if(MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}


void ASTUGameStateBase::StartRound()
{
	RoundCountDown = GameData.RoundsTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameStateBase::GameTimerUpdate, 1.0f, true);
}
