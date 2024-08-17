// Shoot Them Up Game, All Right Reserved


#include "STUBaseCharacter.h"



#include "Components/STUCharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Components/STUWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	
	PrimaryActorTick.bCanEverTick = true;

	
	
	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
	
	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

	
}


void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetMesh());
	check(HealthComponent);
	check(GetMovementComponent())

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
	
	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input


bool ASTUBaseCharacter::IsSprinting() const
{
	return false;
}

float ASTUBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()){return 0.0f;}
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if(!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}


void ASTUBaseCharacter::OnDeath()
{
	//PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire(this);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	
}

void ASTUBaseCharacter::OnHealthChanged(float Health, float HealthDelta){}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

	if(FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

