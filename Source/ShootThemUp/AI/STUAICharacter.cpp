// Shoot Them Up Game, All Right Reserved


#include "AI/STUAICharacter.h"

#include "BrainComponent.h"
#include "STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/WidgetComponent.h"


ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& Objinit)
:Super(Objinit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTUAIController::StaticClass();

	bUseControllerRotationYaw = false;

	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateHealthWidgetVisibility();
}

void ASTUAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
}

void ASTUAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);

	
	if(!HealthWidgetComponent) return;

	
}

void ASTUAICharacter::UpdateHealthWidgetVisibility()
{
	if(!GetWorld() || !GetWorld()->GetFirstPlayerController() ||
	   !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;
	
	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}

void ASTUAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STUController = Cast<AAIController>(Controller);
	if(STUController && STUController->BrainComponent)
	{
		STUController->BrainComponent->Cleanup();
	}
}
