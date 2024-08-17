// Shoot Them Up Game, All Right Reserved


#include "Player/STUPlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ASTUPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(CameraCollisionComponent);
	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionEndOverlap);
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent);
	check(GetCapsuleComponent());
	
	PlayerInputComponent->BindAxis("MoveForward", this,&ASTUPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this,&ASTUPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this,&ASTUPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this,&ASTUPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,&ASTUPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUPlayerCharacter::OnStartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUPlayerCharacter::OnStopSprinting);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}
	
bool ASTUPlayerCharacter::IsSprinting() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}


void ASTUPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUPlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUPlayerCharacter::OnStartSprinting()
{
	WantsToRun = true;
}

void ASTUPlayerCharacter::OnStopSprinting()
{
	WantsToRun = false;
}

void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ASTUPlayerCharacter::CheckCameraOverlap()
{
	const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> MeshChildren;
	GetMesh()->GetChildrenComponents(true, MeshChildren);

	for(const auto MeshChild: MeshChildren)
	{
		const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
		if(MeshChildGeometry)
		{
			MeshChildGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}


void ASTUPlayerCharacter::OnDeath()
{
	Super::OnDeath();
	if(Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}
