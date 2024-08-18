// Shoot Them Up Game, All Right Reserved


#include "STUPlayerController.h"	

#include "STUPlayerState.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "Game/STUGameModeBase.h"
#include "Game/STUGameStateBase.h"


ASTUPlayerController::ASTUPlayerController()
{
	MyRespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld())
	{
		const auto GameState = Cast<ASTUGameStateBase>(GetWorld()->GetAuthGameMode());
		if(GameState)
		{
			GameState->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
		}
		
	}
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMathcState State)
{
	if(State == ESTUMathcState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());

		bShowMouseCursor = true;
	}
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

void ASTUPlayerController::StartRespawn(AController* Controller)
{
	auto GameState = Cast<ASTUGameStateBase>(GetWorld()->GetGameState());
	if (!GameState) return;
	
	const auto RespawnAvailable = GameState->RoundCountDown >
		GameState->MinRoundTimeForRespawn +
		GameState->GetGameData().RespawnTime;
	if(!RespawnAvailable) return;
	const auto RespawnComponent = StuUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
	if(!RespawnComponent) return;
    
	RespawnComponent->Respawn(GameState->GetGameData().RespawnTime);
}

void ASTUPlayerController::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = KillerController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

	if(KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if(VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespawn(VictimController);
}