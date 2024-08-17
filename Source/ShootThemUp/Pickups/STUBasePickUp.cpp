
#include "Pickups/STUBasePickUp.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickUp::ASTUBasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetRootComponent(CollisionComponent);
}


void ASTUBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);
	GenerateRotationYaw();
}
	
void ASTUBasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		
		PickupWasTaken();
	}

}



void ASTUBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

bool ASTUBasePickUp::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
	
}

bool ASTUBasePickUp::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTUBasePickUp::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}


	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickUp::Respawn, RespawnTime);
}

void ASTUBasePickUp::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}

		
}

void ASTUBasePickUp::GenerateRotationYaw()
{
	if(! bIsSpin) return;
	const auto Direction = FMath::RandBool() ? 1.0f: -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

