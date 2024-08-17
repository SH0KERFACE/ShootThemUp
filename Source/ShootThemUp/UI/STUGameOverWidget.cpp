// Shoot Them Up Game, All Right Reserved


#include "UI/STUGameOverWidget.h"

#include "ModuleDescriptor.h"
#include "STUPlayerStatRowWidget.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Game/STUGameModeBase.h"
#include "Game/STUGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUPlayerState.h"

void USTUGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(GetWorld())
	{
		const auto GameState = Cast<ASTUGameStateBase>(GetWorld()->GetAuthGameMode());
		if(GameState)
		{
			GameState->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
		}
	}

	if(ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
	}
}



void USTUGameOverWidget::OnMatchStateChanged(ESTUMathcState State)
{
	if(State == ESTUMathcState::GameOver)
	{
		UpdatePlayerStat();
	}
}

void USTUGameOverWidget::UpdatePlayerStat()
{
	if(!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if(!Controller) continue;

		const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget) return;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(StuUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(StuUtils::TextFromInt(PlayerState->GetDeathNum()));
		PlayerStatRowWidget->SetTeam(StuUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
		PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());
		PlayerStatBox->AddChild(PlayerStatRowWidget);

	}
}

void USTUGameOverWidget::OnResetLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
