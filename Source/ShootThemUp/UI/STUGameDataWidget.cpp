// Shoot Them Up Game, All Right Reserved


#include "UI/STUGameDataWidget.h"

#include "Game/STUGameModeBase.h"
#include "Player/STUPlayerState.h"



int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetStuGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetStuGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundsSecondsRemaining() const
{
	const auto GameMode = GetStuGameMode();
	return GameMode ? GameMode->GetRoundSecondRemaining() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetStuGameMode() const
{
	return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
