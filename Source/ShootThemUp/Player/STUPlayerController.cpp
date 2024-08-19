// Shoot Them Up Game, All Right Reserved


#include "STUPlayerController.h"	



void ASTUPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

