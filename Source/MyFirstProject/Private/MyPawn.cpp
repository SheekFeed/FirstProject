#include "MyPawn.h"

#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(DefaultRoot);

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MainCamera->SetupAttachment(DefaultRoot);

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	MainMesh->SetupAttachment(DefaultRoot);

	MainCamera->SetRelativeLocationAndRotation(FVector(-870.f, 0.f, 360.f), FRotator(-30.f, 0.f, 0.f));
	MainMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (MeshFinder.Succeeded())
	{
		MainMesh->SetStaticMesh(MeshFinder.Object);
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MovementActionFinder(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Movement.IA_Movement'"));
	if (MovementActionFinder.Succeeded())
	{
		MovementActionRef = MovementActionFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> BrakeActionFinder(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Brake.IA_Brake'"));
	if (BrakeActionFinder.Succeeded())
	{
		BrakeActionRef = BrakeActionFinder.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> SpeedActionFinder(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Speed.IA_Speed'"));
	if (SpeedActionFinder.Succeeded())
	{
		SpeedActionRef = SpeedActionFinder.Object;
	}

}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPawn::AddWorldScale()
{
	if ((MainMesh->GetRelativeScale3D().Y > ScaleUpLimiter) || (MainMesh->GetRelativeScale3D().Y < ScaleBottomLimiter))
	{
		ScaleSpeed *= -1.f;
	}

	MainMesh->SetRelativeScale3D(MainMesh->GetRelativeScale3D() + ScaleSpeed);
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EIC = Cast<UEnhancedInputComponent>(InputComponent);

	if (!IsValid(EIC))
	{
		return;
	}
	
	EIC->BindAction(MovementActionRef, ETriggerEvent::Triggered, this, &AMyPawn::MovementAction);
	EIC->BindAction(BrakeActionRef, ETriggerEvent::Triggered, this, &AMyPawn::BrakeAction);
	EIC->BindAction(SpeedActionRef, ETriggerEvent::Triggered, this, &AMyPawn::SpeedAction);
}

void AMyPawn::MovementAction(const FInputActionValue& Value)
{
	float X = Value.Get<FVector2d>().X;
	float Y = Value.Get<FVector2d>().Y;

	AddActorLocalRotation(FRotator(0.f, FMath::Sign(X) * Y, 0.f));
	AddActorLocalOffset(FVector(X * Speed, 0.f, 0.f));
}

void AMyPawn::BrakeAction(const FInputActionValue& Value)
{
	if (Speed > 0) --Speed;
}

void AMyPawn::SpeedAction(const FInputActionValue& Value)
{
	++Speed;
}


void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddWorldScale();
}
