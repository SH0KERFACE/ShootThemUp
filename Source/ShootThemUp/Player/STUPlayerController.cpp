// Shoot Them Up Game, All Right Reserved


#include "STUPlayerController.h"	
#include "Components/STURespawnComponent.h"
#include "Game/STUGameModeBase.h"
#include "Game/STUGameStateBase.h"


ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
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

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
}

void ASTUPlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}
