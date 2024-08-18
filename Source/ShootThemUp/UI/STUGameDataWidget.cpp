// Shoot Them Up Game, All Right Reserved


#include "UI/STUGameDataWidget.h"

#include "Game/STUGameModeBase.h"
#include "Game/STUGameStateBase.h"
#include "Player/STUPlayerState.h"



int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameState = Cast<ASTUGameStateBase>(GetWorld()->GetGameState());
	return GameState ? GameState->GetCurrentRoundNum() : 0;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameState = Cast<ASTUGameStateBase>(GetWorld()->GetGameState());
	return GameState ? GameState->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundsSecondsRemaining() const
{
	const auto GameState = Cast<ASTUGameStateBase>(GetWorld()->GetGameState());
		
	return GameState ? GameState->GetRoundSecondRemaining() : 0;
}



ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
