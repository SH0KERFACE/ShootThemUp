// Shoot Them Up Game, All Right Reserved


#include "UI/STUGameDataWidget.h"

#include "Game/STUGameStateBase.h"




int32 USTUGameDataWidget::GetRoundsSecondsRemaining() const
{
	const auto GameState = Cast<ASTUGameStateBase>(GetWorld()->GetGameState());
		
	return GameState ? GameState->GetRoundSecondRemaining() : 0;
}



