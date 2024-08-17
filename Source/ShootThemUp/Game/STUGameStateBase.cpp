// Shoot Them Up Game, All Right Reserved


#include "Game/STUGameStateBase.h"

void ASTUGameStateBase::SetMatchState(ESTUMathcState State)
{
	if(MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}



